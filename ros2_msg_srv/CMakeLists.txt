cmake_minimum_required(VERSION 3.5)
project(ros2_msg_srv)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(talker_msg src/talker_msg.cpp)
ament_target_dependencies(talker_msg rclcpp std_msgs)

add_executable(listener_msg src/listener_msg.cpp)
ament_target_dependencies(listener_msg rclcpp std_msgs)

rosidl_generate_interfaces(ros2_msg_srv
  "msg/Num.msg"
  "srv/Addthreeint.srv"
  DEPENDENCIES std_msgs
 )

 rosidl_target_interfaces(talker_msg ros2_msg_srv "rosidl_typesupport_cpp")
 rosidl_target_interfaces(listener_msg ros2_msg_srv "rosidl_typesupport_cpp")

 install(TARGETS
  talker_msg
  listener_msg
  DESTINATION lib/ros2_msg_srv)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
