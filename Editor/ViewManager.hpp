#ifndef URDE_VIEW_MANAGER_HPP
#define URDE_VIEW_MANAGER_HPP

#include <HECL/CVarManager.hpp>
#include "ProjectManager.hpp"
#include "Space.hpp"

namespace URDE
{
class SplashScreen;

class ViewManager : public Specter::IViewManager
{
    friend class ProjectManager;
    friend class Space;
    friend class RootSpace;

    HECL::Runtime::FileStoreManager& m_fileStoreManager;
    HECL::CVarManager& m_cvarManager;
    ProjectManager m_projManager;
    Specter::FontCache m_fontCache;
    Specter::DefaultThemeData m_themeData;
    Specter::ViewResources m_viewResources;
    Specter::Translator m_translator;
    std::unique_ptr<boo::IWindow> m_mainWindow;

    std::unique_ptr<Specter::RootView> m_rootView;
    std::unique_ptr<SplashScreen> m_splash;
    std::unique_ptr<RootSpace> m_rootSpace;
    Specter::View* m_rootSpaceView = nullptr;

    HECL::SystemString m_recentProjectsPath;
    std::vector<HECL::SystemString> m_recentProjects;
    HECL::SystemString m_recentFilesPath;
    std::vector<HECL::SystemString> m_recentFiles;

    bool m_updatePf = false;
    float m_reqPf;

    Specter::View* BuildSpaceViews();
    Specter::RootView* SetupRootView();
    SplashScreen* SetupSplashView();
    void RootSpaceViewBuilt(Specter::View* view);
    void SetupEditorView();
    void SetupEditorView(ConfigReader& r);
    void SaveEditorView(ConfigWriter& w);

    bool m_showSplash = false;
    void DismissSplash();

    unsigned m_editorFrames = 120;
    void FadeInEditors() {m_editorFrames = 0;}

    Space* m_deferSplit = nullptr;
    Specter::SplitView::Axis m_deferSplitAxis;
    int m_deferSplitThisSlot;
    boo::SWindowCoord m_deferSplitCoord;

public:
    ViewManager(HECL::Runtime::FileStoreManager& fileMgr, HECL::CVarManager& cvarMgr);
    ~ViewManager();

    Specter::RootView& rootView() const {return *m_rootView;}
    void requestPixelFactor(float pf)
    {
        m_reqPf = pf;
        m_updatePf = true;
    }

    ProjectManager& projectManager() {return m_projManager;}
    HECL::Database::Project* project() {return m_projManager.project();}
    const Specter::Translator* getTranslator() const {return &m_translator;}

    void deferSpaceSplit(Specter::ISpaceController* split, Specter::SplitView::Axis axis, int thisSlot,
                         const boo::SWindowCoord& coord)
    {
        m_deferSplit = static_cast<Space*>(split);
        m_deferSplitAxis = axis;
        m_deferSplitThisSlot = thisSlot;
        m_deferSplitCoord = coord;
    }

    const std::vector<HECL::SystemString>* recentProjects() const {return &m_recentProjects;}
    void pushRecentProject(const HECL::SystemString& path);

    const std::vector<HECL::SystemString>* recentFiles() const {return &m_recentFiles;}
    void pushRecentFile(const HECL::SystemString& path);

    void init(boo::IApplication* app);
    bool proc();
    void stop();
};

}

#endif // URDE_VIEW_MANAGER_HPP
