#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "ros2_msg_srv/msg/num.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher")
  {
    publisher_ = this->create_publisher<ros2_msg_srv::msg::Num>("topic", 10);    // CHANGE
    timer_ = this->create_wall_timer(
    500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = ros2_msg_srv::msg::Num();                               // CHANGE
    message.number = this->count_++;                                        // CHANGE
    RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.number);    // CHANGE
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<ros2_msg_srv::msg::Num>::SharedPtr publisher_;         // CHANGE
  int count_ = 0;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}