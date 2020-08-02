#include "rclcpp/rclcpp.hpp"
#include "ros2_msg_srv/srv/addthreeint.hpp"     // CHANGE

#include <memory>

void add(const std::shared_ptr<ros2_msg_srv::srv::Addthreeint::Request> request,     // CHANGE
          std::shared_ptr<ros2_msg_srv::srv::Addthreeint::Response>       response)  // CHANGE
{
  response->sum = request->a + request->b + request->c;                                       // CHANGE
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld" " c: %ld",   // CHANGE
                request->a, request->b, request->c);                                          // CHANGE
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_server");  // CHANGE

  rclcpp::Service<ros2_msg_srv::srv::Addthreeint>::SharedPtr service =                 // CHANGE
    node->create_service<ros2_msg_srv::srv::Addthreeint>("add_three_ints",  &add);     // CHANGE

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add three ints.");      // CHANGE

  rclcpp::spin(node);
  rclcpp::shutdown();
}