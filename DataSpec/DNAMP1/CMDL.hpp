#ifndef _DNAMP1_CMDL_HPP_
#define _DNAMP1_CMDL_HPP_

#include "../DNACommon/DNACommon.hpp"
#include "../DNACommon/CMDL.hpp"
#include "CMDLMaterials.hpp"
#include "DNAMP1.hpp"
#include "CINF.hpp"
#include "CSKR.hpp"

#include <Athena/FileReader.hpp>

namespace Retro
{
namespace DNAMP1
{

struct CMDL
{
    static bool Extract(const SpecBase& dataSpec,
                        PAKEntryReadStream& rs,
                        const HECL::ProjectPath& outPath,
                        PAKRouter<PAKBridge>& pakRouter,
                        const PAK::Entry& entry,
                        bool force,
                        std::function<void(const HECL::SystemChar*)> fileChanged)
    {
        /* Check for RigPair */
        const PAKRouter<PAKBridge>::RigPair* rp = pakRouter.lookupCMDLRigPair(entry.id);
        CINF cinf;
        CSKR cskr;
        std::pair<CSKR*,CINF*> loadRp(nullptr, nullptr);
        if (rp)
        {
            pakRouter.lookupAndReadDNA(rp->first, cskr);
            pakRouter.lookupAndReadDNA(rp->second, cinf);
            loadRp.first = &cskr;
            loadRp.second = &cinf;
        }

        /* Do extract */
        HECL::BlenderConnection& conn = HECL::BlenderConnection::SharedConnection();
        if (!conn.createBlend(outPath, HECL::BlenderConnection::TypeMesh))
            return false;
        DNACMDL::ReadCMDLToBlender<PAKRouter<PAKBridge>, MaterialSet, std::pair<CSKR*,CINF*>, DNACMDL::SurfaceHeader_1_2, 2>
                (conn, rs, pakRouter, entry, dataSpec, loadRp);
        conn.saveBlend();

#if 1
        return true;
#endif

        /* Cook and re-extract test */
        HECL::ProjectPath tempOut = outPath.getWithExtension(_S(".recook"), true);
        HECL::BlenderConnection::DataStream ds = conn.beginData();
        DNACMDL::Mesh mesh = ds.compileMesh(HECL::TopologyTriStrips, -1);
        ds.close();
        DNACMDL::WriteCMDL<MaterialSet, DNACMDL::SurfaceHeader_1_2, 2>(tempOut, outPath, mesh);

        Athena::io::FileReader reader(tempOut.getAbsolutePath());
        HECL::ProjectPath tempBlend = outPath.getWithExtension(_S(".recook.blend"), true);
        if (!conn.createBlend(tempBlend, HECL::BlenderConnection::TypeMesh))
            return false;
        DNACMDL::ReadCMDLToBlender<PAKRouter<PAKBridge>, MaterialSet, std::pair<CSKR*,CINF*>, DNACMDL::SurfaceHeader_1_2, 2>
                (conn, reader, pakRouter, entry, dataSpec, loadRp);
        return conn.saveBlend();
    }

    static void Name(const SpecBase& dataSpec,
                     PAKEntryReadStream& rs,
                     PAKRouter<PAKBridge>& pakRouter,
                     PAK::Entry& entry)
    {
        DNACMDL::NameCMDL<PAKRouter<PAKBridge>, MaterialSet>(rs, pakRouter, entry, dataSpec);
    }

    static bool Cook(const HECL::ProjectPath& outPath,
                     const HECL::ProjectPath& inPath,
                     const DNACMDL::Mesh& mesh)
    {
        HECL::ProjectPath tempOut = outPath.getWithExtension(_S(".recook"));
        if (mesh.skins.size())
        {
            DNACMDL::Mesh skinMesh = mesh.getContiguousSkinningVersion();
            if (!DNACMDL::WriteCMDL<MaterialSet, DNACMDL::SurfaceHeader_1_2, 2>(tempOut, inPath, skinMesh))
                return false;

            /* Output skinning intermediate */
            auto vertCountIt = skinMesh.contiguousSkinVertCounts.cbegin();
            Athena::io::FileWriter writer(outPath.getWithExtension(_S(".skin")).getAbsolutePath());
            writer.writeUint32Big(skinMesh.skins.size());
            for (const std::vector<DNACMDL::Mesh::SkinBind> skin : skinMesh.skins)
            {
                writer.writeUint32Big(skin.size());
                for (const DNACMDL::Mesh::SkinBind& bind : skin)
                {
                    writer.writeUint32Big(bind.boneIdx);
                    writer.writeFloatBig(bind.weight);
                }
                writer.writeUint32Big(*vertCountIt++);
            }
            writer.writeUint32Big(skinMesh.pos.size());
            writer.writeUint32Big(skinMesh.boneNames.size());
            for (const std::string& boneName : skinMesh.boneNames)
                writer.writeString(boneName);
        }
        else if (!DNACMDL::WriteCMDL<MaterialSet, DNACMDL::SurfaceHeader_1_2, 2>(tempOut, inPath, mesh))
            return false;
        return true;
    }

    static bool HMDLCook(const HECL::ProjectPath& outPath,
                         const HECL::ProjectPath& inPath,
                         const DNACMDL::Mesh& mesh)
    {
        HECL::ProjectPath tempOut = outPath.getWithExtension(_S(".recook"));
        if (mesh.skins.size())
        {
            if (!DNACMDL::WriteHMDLCMDL<HMDLMaterialSet, DNACMDL::SurfaceHeader_1_2, 2>(tempOut, inPath, mesh))
                return false;

            /* Output skinning intermediate */
            Athena::io::FileWriter writer(outPath.getWithExtension(_S(".skin")).getAbsolutePath());
            writer.writeUint32Big(mesh.skinBanks.banks.size());
            for (const DNACMDL::Mesh::SkinBanks::Bank& sb : mesh.skinBanks.banks)
            {
                writer.writeUint32Big(sb.m_boneIdxs.size());
                for (uint32_t bind : sb.m_boneIdxs)
                    writer.writeUint32Big(bind);
            }
            writer.writeUint32Big(mesh.boneNames.size());
            for (const std::string& boneName : mesh.boneNames)
                writer.writeString(boneName);
        }
        else if (!DNACMDL::WriteHMDLCMDL<HMDLMaterialSet, DNACMDL::SurfaceHeader_1_2, 2>(tempOut, inPath, mesh))
            return false;
        return true;
    }
};

}
}

#endif // _DNAMP1_CMDL_HPP_
