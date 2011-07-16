include(InstallRequiredSystemLibraries)


set(PROJECT_DESCRIPTION  "Chart desing software for crochet")
set(PROJECT_VENDOR       "Stitch Works Software")
set(PROJECT_LIFE         "2010-2011")
set(PROJECT_CONTACT      "support@StitchWorksSoftware.com")
set(ORG_WEBSITE          "www.StitchWorksSoftware.com")
set(PROJECT_VERSION      "${SWS_VERSION_MAJOR}.${SWS_VERSION_MINOR}.${SWS_VERSION_PATCH}")
set(PROJECT_COPYRIGHT    "Copyright (c) ${PROJECT_LIFE} ${PROJECT_VENDOR}")
set(PROJECT_MACOSX_ICON  "Crochet Charts.icns")

#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/resources/license.txt")

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VENDOR ${PROJECT_VENDOR})
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR ${SWS_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${SWS_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${SWS_VERSION_PATCH})
set(CPACK_PACKAGE_CONTACT ${PROJECT_CONTACT})
set(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME};${SWS_PROJECT_NAME}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${SWS_PROJECT_NAME}")

if(WIN32)

	set(CPACK_PACKAGE_ICON "C:\\\\Documents and Settings\\\\Brian Milco\\\\My Documents\\\\crochet.git\\\\images\\\\installer.bmp")
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_PACKAGE_NAME "${SWS_PROJECT_NAME}")
    set(CPACK_NSIS_DISPLAY_NAME "${SWS_PROJECT_NAME}")
    set(CPACK_NSIS_CONTACT ${CPACK_PACKAGE_CONTACT})
    set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "${PROJECT_NAME}-${SWS_VERSION_MAJOR}.${SWS_VERSION_MINOR}")

    set(CPACK_CMAKE_MODULES_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/docs/homepage.html" DESTINATION docs)
    set(CPACK_NSIS_MENU_LINKS "docs/homepage.html" "Homepage for ${PROJECT_VENDOR}"
                              "${PROJECT_NAME}_User_Guide_${SWS_VERSION_MAJOR}.${SWS_VERSION_MINOR}.${SWS_VERSION_PATCH}.pdf" "${SWS_PROJECT_NAME} Help")
    # this doesn't work for the NSIS installer
    #set(CPACK_CREATE_DESKTOP_LINKS "crochet.exe")

    set(CPACK_NSIS_CREATE_ICONS_EXTRA "CreateShortCut '\$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${SWS_PROJECT_NAME}.lnk' '\$INSTDIR\\\\${PROJECT_NAME}.exe'")

    # Icon in the add/remove control panel. Must be an .exe file
    set(CPACK_NSIS_INSTALLED_ICON_NAME "${PROJECT_NAME}.exe")

    set(CPACK_NSIS_URL_INFO_ABOUT "${ORG_WEBSITE}")
    set(CPACK_NSIS_HELP_LINK "${ORG_WEBSITE}")

    set(CPACK_NSIS_MUI_FINISHPAGE_RUN "..\${PROJECT_NAME}.exe")

elseif(APPLE)
    set(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
    set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
    set(CPACK_GENERATOR "Bundle")
    set(CPACK_BUNDLE_NAME "${SWS_PROJECT_NAME}")
    set(CPACK_BUNDLE_PLIST "${CMAKE_CURRENT_BINARY_DIR}/Info.plist")
    set(CPACK_BUNDLE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/images/${SWS_PROJECT_NAME}.icns")
    
    set(CPACK_DMG_VOLUME_NAME "${SWS_PROJECT_NAME}")
    set(CPACK_DMG_DS_STORE "${CMAKE_CURRENT_SOURCE_DIR}/resources/mac/MacDmgDsStore")
    set(CPACK_DMG_BACKGROUND_IMAGE "${CMAKE_CURRENT_SOURCE_DIR}/images/dmg_background.png")

    set(CPACK_BINARY_DRAGNDROP ON)

    set(CPACK_OSX_PACKAGE_VERSION "10.4") #min package version
    
    set(MACOSX_BUNDLE_LONG_VERSION_STRING "${SWS_PROJECT_NAME} version ${SWS_VERSION}")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}")
    set(MACOSX_BUNDLE_COPYRIGHT "${PROJECT_COPYRIGHT}. All rights reserved.")

#for more see: http://www.mail-archive.com/cmake@cmake.org/msg05498.html
#and see: http://www.cmake.org/Wiki/CMake:Bundles_And_Frameworks
#plutil command line utility to edit plist files.
#http://rixstep.com/2/20060901,00.shtml
    set(MACOSX_BUNDLE_INFO_STRING "${SWS_PROJECT_NAME} - version ${PROJECT_VERSION}")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}")
    set(MACOSX_BUNDLE_ICON_FILE "${PROJECT_MACOSX_ICON}")
    set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/images/${SWS_PROJECT_NAME}.icns" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.stitchworkssoftware.crochet")
    set(MACOSX_BUNDLE_BUNDLE_NAME "${SWS_PROJECT_NAME}")

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/MacOSXBundleInfo.plist.in
                ${CMAKE_CURRENT_BINARY_DIR}/Info.plist)
    
    install(CODE "
        set(VERSION_STR \"@SWS_VERSION_MAJOR@.@SWS_VERSION_MINOR@.@SWS_VERSION_PATCH@\")
        file(COPY \"@CMAKE_BINARY_DIR@/docs/pdf/@PROJECT_NAME@_User_Guide_@VERSION_STR@.pdf\" 
             DESTINATION \"@CMAKE_BINARY_DIR@/_CPack_Packages/Darwin/Bundle/@PROJECT_NAME@-@VERSION_STR@\")
        file(RENAME \"@CMAKE_BINARY_DIR@/_CPack_Packages/Darwin/Bundle/@PROJECT_NAME@-@VERSION_STR@/@PROJECT_NAME@_User_Guide_@VERSION_STR@.pdf\" 
        \"@CMAKE_BINARY_DIR@/_CPack_Packages/Darwin/Bundle/@PROJECT_NAME@-@VERSION_STR@/User Guide.pdf\")
        " COMPONENT Runtime)


else()
    set(CPACK_GENERATOR "DEB;RPM;STGZ;TBZ2")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Brian Milco")
    set(CPACK_RPM_PACKAGE_LICENSE "Commercial")
    set(CPACK_RPM_PACKAGE_GROUP "Amusements/Graphics")

    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqtgui4 (>= 4:4.7.0), libqtcore4 (>= 4:4.7.0), libqtnetwork4 (>= 4:4.7.0), libqtxml4 (>= 4:4.7.0), libqtsvg4 (>= 4:4.7.0)")

    #depends(qt4 >= 4.7)
    #TODO: finish adding the deb and rpm stuff here.
endif()

include(CPack)
