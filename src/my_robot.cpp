#include <ros/ros.h>

#include <string>

#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

#include <geometry_msgs/PoseStamped.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


class MyRobot
{
public:
    MyRobot() : 
        nh_(),
        sub_rviz_goal_(nh_.subscribe("move_base_simple/goal", 10, &MyRobot::goalMsgs_callback, this)),
        timer_status_publish_(nh_.createTimer(ros::Duration(1.0), &MyRobot::timerStatusPublish_callback, this)) 
    {
        robot_id_ = 0;
        
        // 变量 g_tf_prefix ="robot_X"或"" 用于区分stage仿真与真实turtlebot机器人 
        std::string g_tf_prefix;
        if ( ros::param::get("~tf_prefix", g_tf_prefix) ) {
            std::cout << "Received tf_prefix parameter.  Stage Simulation" << std::endl;
        }
        else {
            std::cout << "No tf_prefix parameter.  TurtleBot Experiment" << std::endl;
        }
        robot_frame_ = tf::resolve(g_tf_prefix, "base_footprint");
        listener.waitForTransform("/map", robot_frame_, ros::Time(0), ros::Duration(10.0));
        
        // Create the string "robot_X/move_base" 
        move_base_str_ = g_tf_prefix + "/move_base";
        ac = new MoveBaseClient(move_base_str_, true);
        ac->waitForServer(ros::Duration(5));
    }
    
    ~MyRobot() 
    {
        delete ac;
    }
    
    void goalMsgs_callback(const geometry_msgs::PoseStamped msg);
    void timerStatusPublish_callback(const ros::TimerEvent& event);
    
    ros::NodeHandle nh_;
    ros::Subscriber sub_rviz_goal_;
    ros::Timer timer_status_publish_;
    
    int robot_id_;
    std::string robot_frame_;
    std::string move_base_str_;
    
    tf::TransformListener listener;
    MoveBaseClient *ac;  // action client for reaching target goals 
};


void MyRobot::goalMsgs_callback(const geometry_msgs::PoseStamped msg)
{
    // Send a goal to move_base
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose = msg;
    ac->sendGoal(goal);
}


void MyRobot::timerStatusPublish_callback(const ros::TimerEvent& event)
{
    double x_robot, y_robot, th_robot; // 机器人当前的位姿 
    // 通过tf获取机器人当前的位姿 
    tf::StampedTransform transform;
    try {
        listener.lookupTransform("/map", robot_frame_, ros::Time(0), transform);
    }
    catch (tf::TransformException &ex) {
        ROS_ERROR("%s",ex.what());
    }
    x_robot = transform.getOrigin().x();
    y_robot = transform.getOrigin().y();
    // tf::Quaternion 
    tf::Quaternion quat = transform.getRotation();
    double roll, pitch, yaw;
    tf::Matrix3x3(quat).getEulerYPR(yaw, pitch, roll);
    th_robot = yaw;  // Yaw around Z axis
    
    // 机器人发布自身位置信息 
    std::cout << "x=" << x_robot << "  y=" << y_robot << "  th=" << th_robot << std::endl;
}


int main(int argc, char** argv)
{
    ros::init( argc, argv, "robot_0" );
    
    MyRobot my_robot;
    
    ros::spin();
    
    return 0;
}
