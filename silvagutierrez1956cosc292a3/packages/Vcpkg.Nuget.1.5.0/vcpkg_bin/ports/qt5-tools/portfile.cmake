include(vcpkg_common_functions)

include(${CURRENT_INSTALLED_DIR}/share/qt5modularscripts/qt_modular_library.cmake)

qt_modular_library(qttools a950a3c1d8e6e92ba200e6834d1f88b8b98b91e3ab2e238aa4d229248f19103e38a06f0a81304ebdae70b96a60c87fdea8caae0181d2114da3e20e9148d08be5)

#file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/tools/qt5-tools/platforminputcontexts)