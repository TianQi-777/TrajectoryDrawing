# TrajectoryDescription
The trajectory of the robot is known and plotted with Pangolin.

# Data description
**trajectory.txt**:Save trajectory information of robot.

**Data storage form**  
Timestamp Translation-x Translation-y Translation-z Quaternion-x Quaternion-y Quaternion-z Quaternion-w

## Additional Prerequisites for this demo
**Pangolin**  
We use [Pangolin](https://github.com/stevenlovegrove/Pangolin) for visualization and interface. 
Dowload and install instructions can be found at: https://github.com/stevenlovegrove/Pangolin.

**Sophus**  
We use [Sophus](https://github.com/strasdat/Sophus) for Lie groups commonly used for 2d and 3d geometric problems. 
Dowload and install instructions can be found at: https://github.com/strasdat/Sophus.

## Build and Run
```
cd XX/XX(include draw_trajectory.cpp ,trajectory.txt and CMakeLists.txt)  
mkdir build  
cd build  
cmake ..  
make -j2  
./draw_trajectory
```

## Result
**Pangolin GUI:** .  
<div align=center>  
  
![](https://github.com/TianQi-777/TrajectoryDrawing/blob/master/Images/trajectory.png)
</div>

