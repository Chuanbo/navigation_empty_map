#include <ros/ros.h>

#include <geometry_msgs/PoseStamped.h>
#include <move_base_msgs/MoveBaseAction.h>

#include <tf/transform_datatypes.h>


int main(int argc, char** argv) {

    ros::init(argc, argv, "publish_goal");
    ros::NodeHandle nh;

    double goal_x, goal_y, goal_theta;
    if (!nh.getParam("goal_x", goal_x))
        goal_x = 5.0;
    if (!nh.getParam("goal_y", goal_y))
        goal_y = -1.0;
    if (!nh.getParam("goal_theta", goal_theta))
        goal_theta = 0;

    // Send a goal to move_base
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "/map";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = goal_x;
    goal.target_pose.pose.position.y = goal_y;

    // Convert the Euler angle to quaternion
    double radians = goal_theta * (M_PI/180);
    tf::Quaternion quaternion;
    quaternion = tf::createQuaternionFromYaw(radians);

    geometry_msgs::Quaternion qMsg;
    tf::quaternionTFToMsg(quaternion, qMsg);
    goal.target_pose.pose.orientation = qMsg;


    ros::Publisher goal_pub = nh.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1, true);

    geometry_msgs::PoseStamped msg;
    msg = goal.target_pose;

    goal_pub.publish(msg);

    ros::Duration(10.0).sleep();

    return 0;
}
