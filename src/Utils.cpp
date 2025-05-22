#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

namespace PolygonalLibrary
{
	
	
	
	
// TODO controllo su p
bool costruzione_poliedro(int q, PolygonalMesh& mesh){
	
	if (q==3){
		//Cell0Ds
		mesh.NumCell0Ds=4;
		mesh.Cell0DsId = {0,1,2,3}; 
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
		mesh.Cell0DsCoordinates.col(0) << 1.0/sqrt(3), 1.0/sqrt(3), 1.0/sqrt(3);
		mesh.Cell0DsCoordinates.col(1) << -1.0/sqrt(3), -1.0/sqrt(3), 1.0/sqrt(3);
		mesh.Cell0DsCoordinates.col(2) << -1.0/sqrt(3), 1.0/sqrt(3), -1.0/sqrt(3);
		mesh.Cell0DsCoordinates.col(3) << 1.0/sqrt(3), -1.0/sqrt(3), -1.0/sqrt(3);

		//Cell1Ds
		mesh.NumCell1Ds=6;
		mesh.Cell1DsId = {0,1,2,3,4,5}; 
		
		mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
		mesh.Cell1DsExtrema.col(0) << 0, 1 ;
		mesh.Cell1DsExtrema.col(1) << 0, 2 ;
		mesh.Cell1DsExtrema.col(2) << 0, 3 ;
		mesh.Cell1DsExtrema.col(3) << 1, 2 ;
		mesh.Cell1DsExtrema.col(4) << 1, 3 ;
		mesh.Cell1DsExtrema.col(5) << 2, 3 ;
		
		//Cell2Ds
		mesh.NumCell2Ds = 4;
		mesh.Cell2DsId = {0, 1 ,2, 3};
		mesh.Cell2DsNumVert = {3, 3, 3, 3};
		mesh.Cell2DsNumEdg = {3, 3, 3, 3};
		
		
		mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds); 
		
		vector<unsigned int> v1 = {0,1,2};
		vector<unsigned int> v2 = {1,2,3};
		vector<unsigned int> v3 = {0,2,3};
		vector<unsigned int> v4 = {0,1,3};
		
		mesh.Cell2DsVertices= {v1, v2, v3, v4};
		
		mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> e1 = {0,3,1};
		vector<unsigned int> e2 = {3,5,4};
		vector<unsigned int> e3 = {1,5,2};
		vector<unsigned int> e4 = {0,4,2};
		
		mesh.Cell2DsEdges = {e1, e2, e3, e4};
		
		//Cell3Ds
		mesh.Cell3DsId=0; //caso tetraedro
		
		mesh.Cell3DsNumVert = mesh.NumCell0Ds;
		mesh.Cell3DsNumEdg = mesh.NumCell1Ds;
		mesh.Cell3DsNumFaces = mesh.NumCell2Ds;
		
		mesh.Cell3DsVertices = mesh.Cell0DsId; //costruttore di copia? 
		mesh.Cell3DsEdges = mesh.Cell1DsId;
		mesh.Cell3DsFaces = mesh.Cell2DsId;
		
		
		}

	else if (q==4){
		//Cell0Ds
		mesh.NumCell0Ds=6;
		mesh.Cell0DsId = {0,1,2,3,4,5}; // è efficiente? reserve?
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
		
		mesh.Cell0DsCoordinates.col(0) << 1.0, 0.0, 0.0;
		mesh.Cell0DsCoordinates.col(1) << -1.0, 0.0, 0.0;
		mesh.Cell0DsCoordinates.col(2) << 0.0, 0.0, 1.0;
		mesh.Cell0DsCoordinates.col(3) << 0.0, 0.0, -1.0;
		mesh.Cell0DsCoordinates.col(4) << 0.0, 1.0, 0.0;
		mesh.Cell0DsCoordinates.col(5) << 0.0, -1.0, 0.0;
		
		
		//Cell1Ds
		mesh.NumCell1Ds=12;
		mesh.Cell1DsId = {0,1,2,3,4,5,6,7,8,9,10,11};
		
		mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
		mesh.Cell1DsExtrema.col(0) << 0, 2;
		mesh.Cell1DsExtrema.col(1) << 0, 3;
		mesh.Cell1DsExtrema.col(2) << 0, 4;
		mesh.Cell1DsExtrema.col(3) << 0, 5;
		mesh.Cell1DsExtrema.col(4) << 1, 2;
		mesh.Cell1DsExtrema.col(5) << 1, 3;
		mesh.Cell1DsExtrema.col(6) << 1, 4;
		mesh.Cell1DsExtrema.col(7) << 1, 5;
		mesh.Cell1DsExtrema.col(8) << 2, 4;
		mesh.Cell1DsExtrema.col(9) << 2, 5;
		mesh.Cell1DsExtrema.col(10) << 3, 4;
		mesh.Cell1DsExtrema.col(11) << 3, 5;
		
		//Cell2Ds
		mesh.NumCell2Ds = 8;
		mesh.Cell2DsId = {0, 1 ,2, 3, 4, 5, 6, 7};
		mesh.Cell2DsNumVert = {3, 3, 3, 3, 3, 3, 3, 3};
		mesh.Cell2DsNumEdg = {3, 3, 3, 3, 3, 3, 3, 3};
		
		
		mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> v1 = {0,2,4};
		vector<unsigned int> v2 = {1,2,4};
		vector<unsigned int> v3 = {1,2,5};
		vector<unsigned int> v4 = {0,2,5};
		vector<unsigned int> v5 = {0,3,5};
		vector<unsigned int> v6 = {1,3,5};
		vector<unsigned int> v7 = {1,3,4};
		vector<unsigned int> v8 = {0,3,4};

		
		mesh.Cell2DsVertices= {v1, v2, v3, v4, v5, v6, v7, v8};
		
		mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> e1 = {0,8,2};
		vector<unsigned int> e2 = {4,8,6};
		vector<unsigned int> e3 = {4,9,7};
		vector<unsigned int> e4 = {0,9,3};
		vector<unsigned int> e5 = {1,11,3};
		vector<unsigned int> e6 = {5,11,7};
		vector<unsigned int> e7 = {5,10,6};
		vector<unsigned int> e8 = {1,10,2};
		
		mesh.Cell2DsEdges = {e1, e2, e3, e4, e5, e6, e7, e8};
		
		//Cell3D
		
		vector<unsigned int> Cell3DsNumVert = {6};
		vector<unsigned int> Cell3DsNumEdg = {12};
		vector<unsigned int> Cell3DsNumFaces = {8};
	
		vector<unsigned int> Cell3DsVertices = {0, 1, 2, 3, 4, 5};
		vector<unsigned int> Cell3DsEdges = {0,1,2,3,4,5,6,7,8,9,10,11};
		vector<unsigned int> Cell3DsFaces = {0, 1 ,2, 3, 4, 5, 6, 7};
		}
		
		
		
	else if (q==5){
		//Cell0Ds
		mesh.NumCell0Ds=12;
		mesh.Cell0DsId = {0,1,2,3,4,5,6,7,8,9,10,11}; 
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
		double phi = (1+sqrt(5))/2;
		double X = 1/(sqrt(1+pow(phi,2)));
		double Y = phi/(sqrt(1+pow(phi,2)));
		
		mesh.Cell0DsCoordinates.col(0) << -X, Y, 0.0;
		mesh.Cell0DsCoordinates.col(1) << X, -Y, 0.0;
		mesh.Cell0DsCoordinates.col(2) << X, Y, 0.0;
		mesh.Cell0DsCoordinates.col(3) << -X, -Y, 0.0;
		mesh.Cell0DsCoordinates.col(4) << 0.0, X, Y;
		mesh.Cell0DsCoordinates.col(5) << 0.0, -X, -Y;
		mesh.Cell0DsCoordinates.col(6) << 0.0, -X, Y;
		mesh.Cell0DsCoordinates.col(7) << 0.0, X, -Y;
		mesh.Cell0DsCoordinates.col(8) << -Y, 0.0, X;
		mesh.Cell0DsCoordinates.col(9) << -Y, 0.0, -X;
		mesh.Cell0DsCoordinates.col(10) << Y, 0.0, X;
		mesh.Cell0DsCoordinates.col(11) << Y, 0.0, -X;

		
		//Cell1Ds
		mesh.NumCell1Ds=30;
		mesh.Cell1DsId = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29}; // è efficiente? reserve? Vanno ordinati?
		
		mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
		mesh.Cell1DsExtrema.col(0) << 0, 2;
		mesh.Cell1DsExtrema.col(1) << 0, 4;
		mesh.Cell1DsExtrema.col(2) << 0, 7;
		mesh.Cell1DsExtrema.col(3) << 0, 8;
		mesh.Cell1DsExtrema.col(4) << 0, 9;
		mesh.Cell1DsExtrema.col(5) << 1, 3;
		mesh.Cell1DsExtrema.col(6) << 1, 6;
		mesh.Cell1DsExtrema.col(7) << 1, 5;
		mesh.Cell1DsExtrema.col(8) << 1, 10;
		mesh.Cell1DsExtrema.col(9) << 1, 11;
		mesh.Cell1DsExtrema.col(10) << 2, 4;
		mesh.Cell1DsExtrema.col(11) << 2, 7;
		mesh.Cell1DsExtrema.col(12) << 2, 11;
		mesh.Cell1DsExtrema.col(13) << 2, 10;
		mesh.Cell1DsExtrema.col(14) << 3, 5;
		mesh.Cell1DsExtrema.col(15) << 3, 9;
		mesh.Cell1DsExtrema.col(16) << 3, 8;
		mesh.Cell1DsExtrema.col(17) << 3, 6;
		mesh.Cell1DsExtrema.col(18) << 4, 10;
		mesh.Cell1DsExtrema.col(19) << 4, 6;
		mesh.Cell1DsExtrema.col(20) << 4, 8;
		mesh.Cell1DsExtrema.col(21) << 5, 11;
		mesh.Cell1DsExtrema.col(22) << 5, 7;
		mesh.Cell1DsExtrema.col(23) << 5, 9;
		mesh.Cell1DsExtrema.col(24) << 6, 8;
		mesh.Cell1DsExtrema.col(25) << 6, 10;
		mesh.Cell1DsExtrema.col(26) << 7, 9;
		mesh.Cell1DsExtrema.col(27) << 7, 11;
		mesh.Cell1DsExtrema.col(28) << 8, 9;
		mesh.Cell1DsExtrema.col(29) << 10, 11;
		
		
		//Cell2Ds
		mesh.NumCell2Ds = 20;
		mesh.Cell2DsId = {0, 1 ,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
		mesh.Cell2DsNumVert = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
		mesh.Cell2DsNumEdg = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
		
		
		mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> v1 = {0,2,4};
		vector<unsigned int> v2 = {0,4,8};
		vector<unsigned int> v3 = {0,8,9};
		vector<unsigned int> v4 = {0,7,9};
		vector<unsigned int> v5 = {0,2,7};
		vector<unsigned int> v6 = {2,7,11};
		vector<unsigned int> v7 = {5,7,11};
		vector<unsigned int> v8 = {5,7,9};
		vector<unsigned int> v9 = {3,5,9};
		vector<unsigned int> v10 = {3,8,9};
		vector<unsigned int> v11 = {3,6,8};
		vector<unsigned int> v12 = {4,6,8};
		vector<unsigned int> v13 = {4,6,10};
		vector<unsigned int> v14 = {1,6,10};
		vector<unsigned int> v15 = {1,3,6};
		vector<unsigned int> v16 = {1,3,5};
		vector<unsigned int> v17 = {1,5,11};
		vector<unsigned int> v18 = {1,10,11};
		vector<unsigned int> v19 = {2,10,11};
		vector<unsigned int> v20 = {2,4,10};

		
		mesh.Cell2DsVertices= {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20};
		
		mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> e1 = {0,10,1};
		vector<unsigned int> e2 = {1,20,3};
		vector<unsigned int> e3 = {3,28,4};
		vector<unsigned int> e4 = {2,26,4};
		vector<unsigned int> e5 = {0,11,2};
		vector<unsigned int> e6 = {11,27,12};
		vector<unsigned int> e7 = {22,27,21};
		vector<unsigned int> e8 = {22,26,23};
		vector<unsigned int> e9 = {14,23,15};
		vector<unsigned int> e10 = {16,28,15};
		vector<unsigned int> e11 = {17,24,16};
		vector<unsigned int> e12 = {19,24,20};
		vector<unsigned int> e13 = {19,25,18};
		vector<unsigned int> e14 = {6,25,8};
		vector<unsigned int> e15 = {5,17,6};
		vector<unsigned int> e16 = {5,14,7};
		vector<unsigned int> e17 = {7,21,9};
		vector<unsigned int> e18 = {8,29,9};
		vector<unsigned int> e19 = {13,29,12};
		vector<unsigned int> e20 = {10,18,13};
		
		mesh.Cell2DsEdges = {e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20};
		
		//Cell3D
		
		vector<unsigned int> Cell3DsNumVert = {12};
		vector<unsigned int> Cell3DsNumEdg = {30};
		vector<unsigned int> Cell3DsNumFaces = {20};
	
		vector<unsigned int> Cell3DsVertices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
		vector<unsigned int> Cell3DsEdges = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29};
		vector<unsigned int> Cell3DsFaces = {0, 1 ,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
		}
		
		
		
	else{
		cerr<<"valore di q non valido"<<endl;
		return false;
	}
	
	return true;
}


bool check_ed_vert(const PolygonalMesh& mesh){
	for (unsigned int i=0; i<mesh.NumCell2Ds; i++){
		for (unsigned int j=0; j<(mesh.Cell2DsEdges[i]).size(); j++){
			
			unsigned int vert_id = mesh.Cell2DsVertices[i][j];
			unsigned int ed_id = mesh.Cell2DsEdges[i][j];
			unsigned int next_ed_id = mesh.Cell2DsEdges[i][(j+1)%(mesh.Cell2DsEdges[i]).size()];
			unsigned int count =0;
			
			//Controllo Lati
			if (mesh.Cell1DsExtrema(0,ed_id) == mesh.Cell1DsExtrema(0,next_ed_id))
				count++;
			if (mesh.Cell1DsExtrema(0,ed_id) == mesh.Cell1DsExtrema(1,next_ed_id))
				count++;
			if (mesh.Cell1DsExtrema(1,ed_id) == mesh.Cell1DsExtrema(0,next_ed_id))
				count++;
			if (mesh.Cell1DsExtrema(1,ed_id) == mesh.Cell1DsExtrema(1,next_ed_id))
				count++;
			
			if (count != 1){
				cout<<"lati: "<<count<<" i: "<<i<<" j: "<<j<<endl;
				return false;
			}
			
			// Controllo Vertici
			if (vert_id == mesh.Cell1DsExtrema(0,ed_id))
				count++;
			if (vert_id == mesh.Cell1DsExtrema(1,ed_id))
				count++;
			
			if (count != 2){
				cout<<"vertici: "<<count<<" i: "<<i<<" j: "<<j<<endl;
				return false;
			}
			
			
		}
			
	}
	return true;
}

bool new_vert(vector<array<double,3>>& verts, array<double,3> v0, array<double,3> v1, unsigned int j,unsigned int& count){
	
	for (unsigned int i=0; i< j-1; i++){
		
		array<double,3> new_vert;
		new_vert={v0[0]+(v1[0]-v0[0])*(i+1)/j,v0[1]+(v1[1]-v0[1])*(i+1)/j,v0[2]+(v1[2]-v0[2])*(i+1)/j};
		if (find(verts.begin(), verts.end(), new_vert) == verts.end()) {
						verts.push_back(new_vert);
						cout<<"vertice "<<count<<":"<<endl;
						for (unsigned int j=0;j<3;j++){
							cout<<new_vert[j]<<" ";
						}
						cout<<endl;
						count++;
		}
		
	}	
	return true;
		
}

vector<array<double,3>> triang_vert(PolygonalMesh& mesh, unsigned int b){
	vector<array<double,3>> verts;
	unsigned int count= mesh.NumCell2Ds;
	for (unsigned int i=0; i<mesh.NumCell2Ds; i++){
		
		cout<<"Faccia"<< i<<":"<<endl;
		cout<<endl;
		unsigned int id_0 = mesh.Cell2DsVertices[i][0];
		unsigned int id_1 = mesh.Cell2DsVertices[i][1];
		unsigned int id_2 = mesh.Cell2DsVertices[i][2];
		array<double,3> v0= {mesh.Cell0DsCoordinates(0,id_0),mesh.Cell0DsCoordinates(1,id_0),mesh.Cell0DsCoordinates(2,id_0)};
		array<double,3> v1= {mesh.Cell0DsCoordinates(0,id_1),mesh.Cell0DsCoordinates(1,id_1),mesh.Cell0DsCoordinates(2,id_1)};
		array<double,3> v2= {mesh.Cell0DsCoordinates(0,id_2),mesh.Cell0DsCoordinates(1,id_2),mesh.Cell0DsCoordinates(2,id_2)};
		
		for(unsigned int j=b; j>0; j--){
			if (new_vert(verts, v0, v1, j,count)){
				if (j!=1){
					v0={v0[0]+(v2[0]-v0[0])/b,v0[1]+(v2[1]-v0[1])/b,v0[2]+(v2[2]-v0[2])/b};
					v1={v1[0]+(v2[0]-v1[0])/b,v1[1]+(v2[1]-v1[1])/b,v1[2]+(v2[2]-v1[2])/b};
					if (find(verts.begin(), verts.end(), v0) == verts.end()) {
						verts.push_back(v0);
						cout<<"vertice "<<count<<":"<<endl;
						for (unsigned int k=0;k<3;k++){
							cout<<v0[k]<<" ";
						}
						cout<<endl;
						count++;
					}
					if (find(verts.begin(), verts.end(), v1) == verts.end()) {
						verts.push_back(v1);
						cout<<"vertice "<<count<<":"<<endl;
						for (unsigned int k=0;k<3;k++){
							cout<<v1[k]<<" ";
						}
						cout<<endl;
						count++;
					}
				}
			
		
		cout<<endl;
		
			}
		}
	}
	return verts;

}
}