#pragma once

// ���� SDKDDKVer.h ��������õ���߰汾�� Windows ƽ̨��

// ����?Ϊ��ǰ�� Windows ƽ̨����Ӧ�ó��������? WinSDKVer.h������
// WIN32_WINNT ������ΪҪ֧�ֵ�ƽ̨��Ȼ���ٰ��� SDKDDKVer.h��
#include"kthshortestpathalg.h"
#include <SDKDDKVer.h>
#include<string>
#include"stdafx.h"

class RWA
{
public:
	std::string instancesname ;//������
	/*����α�������Ѱ��·��?*/
	int  **visit_edge , *visit_vec , *prt , *d , *tempS ;
	int  **RouteS , **BestRouteS , *ColorS , *BestColorS ;//·���⣬��ɫ��
	int  *RouteIndex ;
	int  **Mat , **CopyMat , **ChartMat ;//�������? ���������ж�Ӧ����
	int  **IncChart; //������
	int  **IncChartt;
	int  **IncChartCopy ; //����������
	int  **LightPath , *LPNum ; 
	int  N , LP , Edge ; //��������LightPath��,����
	int  Color ; 
	int  **LIDC , **BestLIDC ; //��¼��ÿ����ɫ��LightPath��
	int  *Conflict , *ConflictCopy ; //��ǰ���Ӧ��ÿ��LightPath�ĳ�ͻ��
	int  AllConflict , BestAllConflict ; //����LightPath�ĳ�ͻ��
	int  *Tabu ;//���� 
	int  *TabuTenure2;
	int  *BR ;//��·ʱ������¼��ǰ���ͻλ��?
	int  *path ;
	int  *loc ;//���ڼ�¼һ����·�ϵ�����������
	int  *weight;

	int** NewGraph;//��¼�е��������߸Ķ���ͼ
	int  *ReplaceLoc;//���ڼ�¼�ֲ��޸���ɫ�ĸĶ�
	int  **LPVariation;//����ͳ��һ����·��·���ϰ���������������?��һά��Edge����ά��Color��ֵ������·����
	int  *MixWeight;//����ͳ���Ѿ���������ɫ������ʹ������������ɫ��С��
	std::vector<int> DFLP ;
	int **dist ;
public:
	int  **GetMat(){return Mat;}
	void InitRoom () ;//�ռ�����
	void InitSolution() ;//��ʼ����
	void InitIncChart() ;//��ʼ��������
	void InitMat() ;
	void InitLightpath();
	int Check() ;
	void print() ;
	void LocalSearch() ;//�ֲ�����
	bool ChangeRoute() ;//����·��
	void UpdataPert(int,int);//�Ŷ�ʱѰ���µĲ���·�������?
	void RecoverAndCopy( bool ) ;
	bool ReplaceRoute() ;//·���滻
	int Estimation( int , int* ) ;//·������
	void UpdataRoute(int,int*);//����·��
	bool ChangeColor() ;//������ɫ
	void SubColor() ;//��ȥһ����ɫ
	int EstimationOfChgColor(int ,int);//������ɫ�任���Ŀ��?��ֵ
	void UpdataIncChart(int,int);//�任��ɫ�����������?
	void MixChange(bool);//��ϱ�?
	void UpdataMixChg(int ,int , int*) ;
	void Perturbation() ;
	int *Pseudo_BFS(int) ;
	int *Pseudo_DFS(int,int);
	int *Pseudo_DFS( int );
	void SA_DFS();
	void RecordFile() ;
	void ExChgColor();
	void UpdataExChgCor(int,int);
	void EjCRoute() ;
	void InsetRoute(int,int);
	void UpdataCorRotChg(int,int);
	void Fetch_Insert();
	void Fetch_Lp(int);
	void Inset_Lp(int);
	void UpdataInset(int ,int,int*) ;
	void floyd();//������������֮����������
	bool FindShortRoute();
	void Perturb(int strength);
	void Perturb_o(int minvalue);
	void InitNewGraph();
	int EstimationOfCandC(int lp,int weight);
	void UpdateLPVariation(int lp);
	//void InitAvailableColor(int lp);
	int ReplaceColor(int lp, int* route);
	bool ColorConnection();
};