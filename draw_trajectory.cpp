#include <sophus/se3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <pangolin/pangolin.h>

using namespace std;

string trajectory_file = "../trajectory.txt";

void DrawTrajectory(vector<Sophus::SE3, Eigen::aligned_allocator<Sophus::SE3>>);

int main(int argc, char **argv) {

    vector<Sophus::SE3, Eigen::aligned_allocator<Sophus::SE3>> poses;

    ifstream fin(trajectory_file);
    if (!fin)
    {
        cerr<<"请在有trajectory.txt的目录下运行此程序"<<endl;
        return 1;
    }
    while (fin)
    {
        double data[8] = {0}; //其中data1[0]表示时间，跳过（略去）
        for ( auto& d:data )
            fin >> d;

        //cout<<" "<<data[0]<<" "<<data[1]<<" "<<data[2]<<" "<<data[3]<<" "<<data[4]<<" "<<data[5]<<" "<<data[6]<<" "<<data[7]<<"\n";  //查看输出结果

        Eigen::Vector3d t(data[1], data[2], data[3]); //获取平移数据

        Eigen::Quaterniond q( data[7], data[4], data[5], data[6] );//获取旋转数据，注意输入是实1,虚1,虚2,虚3

        Sophus::SE3 T(q,t);//获取李群一组（行）数据的SE3
        poses.push_back( T );//将真实轨迹原SE3存入T

    }

    poses.pop_back();  //删除最后的0元素
    DrawTrajectory(poses);
    return 0;
}

/*******************************************************************************************/
void DrawTrajectory(vector<Sophus::SE3, Eigen::aligned_allocator<Sophus::SE3>> poses) {
    if (poses.empty()) {
        cerr << "Trajectory is empty!" << endl;
        return;
    }

    pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );

    pangolin::View &d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -1024.0f / 768.0f)
            .SetHandler(new pangolin::Handler3D(s_cam));


    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glLineWidth(2);
        for (size_t i = 0; i < poses.size() - 1; i++) {
            glColor3f(1 - (float) i / poses.size(), 0.0f, (float) i / poses.size());
            glBegin(GL_LINES);
            auto p1 = poses[i], p2 = poses[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();
        }
        pangolin::FinishFrame();
        usleep(5000);   // sleep 5 ms
    }

}
