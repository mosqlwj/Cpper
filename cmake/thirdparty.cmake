
############################################################
# 添加json库
add_library(json INTERFACE )
target_include_directories(json INTERFACE ${HOME_THIRDPARTY}/nlohmann)

############################################################
# 添加test库
add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE ${HOME_THIRDPARTY}/doctest)


############################################################
# 添加cli11库
add_library(cli11 INTERFACE)
target_include_directories(cli11 INTERFACE ${HOME_THIRDPARTY}/cli11)