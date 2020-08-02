#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "ros2_msg_srv/msg/num.hpp"     // CHANGE
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<ros2_msg_srv::msg::Num>(          // CHANGE
      "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const ros2_msg_srv::msg::Num::SharedPtr msg) const       // CHANGE
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg->number);              // CHANGE
  }
  rclcpp::Subscription<ros2_msg_srv::msg::Num>::SharedPtr subscription_;       // CHANGE
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}