// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// RWA.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"
#include <math.h>
#include<algorithm>
#include "RWA.h"
float start;
void RWA::InitRoom( )
{
	//cout<<"InitRoom..."<<endl;
	int i ,j , k  ;
	//���������丱��
	IncChart = (int**)malloc(sizeof(int*)*LP);
	IncChartt=(int**)malloc(sizeof(int*)*LP);
	IncChartCopy = (int**)malloc(sizeof(int*)*LP);
	for ( i = 0 ; i < LP ; i++ )
	{
		IncChartCopy[i] = (int*)malloc(sizeof(int)*Edge);
		IncChart[i] = (int*)malloc(sizeof(int)*Edge);
		memset(IncChart[i],0,sizeof(int)*Edge);
		IncChartt[i] = (int*)malloc(sizeof(int)*Edge);
		memset(IncChartt[i],0,sizeof(int)*Edge);
		memset(IncChartCopy[i],0,sizeof(int)*Edge);
	}

	RouteIndex = (int*)malloc(sizeof(int)*LP);//��ʼ��������
	RouteS = (int**)malloc(sizeof(int*)*LP) ;
	BestRouteS = (int**)malloc(sizeof(int*)*LP) ;
	for ( i = 0 ; i < LP ; i++ )
	{
		RouteS[i] = (int*)malloc(sizeof(int)*N) ;
		BestRouteS[i] = (int*)malloc(sizeof(int)*N) ;
		memset(RouteS[i],-1,sizeof(int)*N);
		memset(BestRouteS[i],-1,sizeof(int)*N);
	}
	ColorS = (int*)malloc(sizeof(int)*LP);
	BestColorS = (int*)malloc(sizeof(int)*LP);

	Conflict = (int *)malloc(sizeof(int)*LP);
	ConflictCopy = (int *)malloc(sizeof(int)*LP);

	LPNum = (int *)malloc(sizeof(int)*LP);

	BR= (int*)malloc(sizeof(int)*N);//����·��

	path = new int[Edge];
	loc = (int *)malloc(sizeof(int)*Edge);
	ReplaceLoc = (int *)malloc(sizeof(int) * Edge);

	//int **visit_edge , *visit_vec , *prt , *d , *tempS ;
	visit_edge = (int**)malloc(sizeof(int*)*N);
	for ( i = 0 ; i < N ; i++ )
	{
		visit_edge[i] = (int*)malloc(sizeof(int)*N) ;
	}
	visit_vec = (int*)malloc(sizeof(int)*N);
	prt = (int*)malloc(sizeof(int)*N);
	d = (int*)malloc(sizeof(int)*N);
	tempS = (int*)malloc(sizeof(int)*N);

	dist = (int**)malloc(sizeof(int*)*N);
	for ( i = 0 ; i < N ; i++ )
	{
		dist[i] = (int*)malloc(sizeof(int)*N);
		memset(dist[i],0,sizeof(int)*N);
	}

	LPVariation = (int**)malloc(sizeof(int*) * (Edge));
	
	for (i = 0; i < Edge; i++)
	{
		LPVariation[i] = (int*)malloc(sizeof(int*) * (Color));
		memset(LPVariation[i], 0, sizeof(int*) * (Color));
		
	}
	MixWeight = (int*)malloc(sizeof(int) * (LP));
	memset(MixWeight, INT_MAX, sizeof(int) * LP);
	weight=(int*)malloc(sizeof(int)*LP);
	memset(weight,1,sizeof(int)*LP);

}
void RWA::InitMat()
{
	int i  ;
	/*string netname ;
	cout<<"input netname: ";
	cin>>netname ;
	string Filename("E:\\612\\personal\\yanshengfeng\\instances\\rwa_instances\\instances\\set_y\\");
	Filename = Filename + netname +".net" ;*/
	string Filename("rwa_instances\\instances\\set_y\\Y.3_seed=1.net");//Y.3.1.netZ.4x25 Z.10x10.net
	ifstream fin(Filename.c_str());
	 if ( fin.fail() )
     {
           cout << "### Erreur open, File_Name " << Filename << endl;
           exit(0);
     }
     if ( fin.eof() )
     {
           cout << "### Error open, File_Name " << Filename << endl;
           exit(0);
     }
	 fin>>N>>Edge ;//�����ͱ���
	 //MAX_VERTEX = N ;//����K���·ʱ�õ�MAX_VERTEX
	 try
	 {
		 /*�ռ�����*/
		 Mat = (int**)malloc(sizeof(int*)*(N));
		 CopyMat = (int**)malloc(sizeof(int*)*(N));
		 ChartMat = (int**)malloc(sizeof(int*)*N);
		 for ( i = 0 ; i < N ; i++ )
		 {
			 Mat[i] = (int*)malloc(sizeof(int)*(N)) ;
			 CopyMat[i] = (int*)malloc(sizeof(int)*(N)) ;
			 ChartMat[i] = (int*)malloc(sizeof(int)*N);
		
			 memset(Mat[i],0,sizeof(int)*N);
			 memset(CopyMat[i],0,sizeof(int)*N);
			 memset(ChartMat[i],-1,sizeof(int)*N);
		 }
		 /*��ֵ��������λ��*/
		 int count = 0;
		 int v1 , v2 ;
		 for ( i = 0 ; i < Edge ; i++ )
		 {
			 fin>>v1>>v2 ;
			 Mat[v1][v2] = 1 ;
			 CopyMat[v1][v2] = 1 ;
			 ChartMat[v1][v2] = count;
			 ++count;
		 }
	 }
	 catch (...)
	 {
		 cout<<"RoomApply or Read value error!!"<<endl ;
	 }
	fin.close();
}
void RWA::InitLightpath( )
{
	int i , j ;//"Z.4x25.20.trf" ;
	instancesname = "Y.3.20_seed=1.trf";//"Y.3.20.5.trf";
	//cout<<"input instancename: ";
	//cin>>instancesname ;
	//string Filename("E:\\612\\personal\\yanshengfeng\\instances\\rwa_instances\\instances\\set_y\\");//Y.3.20.2.trf 
	//Filename = Filename+instancesname+".trf" ;/*"E:\\SVN\\rwa_instances\\instances\\set_y*/
	string Filename("rwa_instances\\instances\\set_y\\");//Y.3.20.2.trf
	Filename = Filename+instancesname ;

	ifstream fin(Filename.c_str());
	 if ( fin.fail() )
     {
           cout << "### Erreur open, File_Name " << Filename << endl;
           exit(0);
     }
     if ( fin.eof() )
     {
           cout << "### Error open, File_Name " << Filename << endl;
           exit(0);
     }
	 fin>>LP ;//�����ͱ���
	 try
	 {
		 /*�ռ�����*/
		 LightPath = (int**)malloc(sizeof(int*)*N);
		 for ( i = 0 ; i < N ; i++ )
		 {
			 LightPath[i] = (int*)malloc(sizeof(int)*N);
			 memset(LightPath[i],0,sizeof(int)*N);
		 }
		 /*��ֵ*/
		 int v1 , v2 ;
		 for ( i = 0 ; i < LP ; i++ )
		 {
			 fin>>v1>>v2 ;
			 LightPath[v1][v2] = 1 ;
		 }
	 }
	 catch (...)
	 {
		 cout<<"RoomApply or Read value error!!"<<endl ;
	 }
	fin.close();
	//print() ;
}

void RWA::floyd( )//������������֮����������
{
	int i , j , k ;
	for ( i = 0 ; i < N ; i++ )
	{
		for( j = 0 ; j < N ; j++ )
		{
			dist[i][j] = Mat[i][j];
			if ( i != j && dist[i][j] == 0 )
			{
				dist[i][j] = INT_MAX ;//��INT_MAX��ʾ�����?��ʾ����������֮��ľ���?
			}
		}
	}
	for( k = 0 ; k < N ; k++ )
	{
		for ( i = 0 ; i < N ; i++ )
		{
			for ( j = 0 ; j < N ; j++ )
			{
				if ( dist[i][k]+dist[k][j] < dist[i][j] &&dist[i][k]!= INT_MAX&&dist[k][j]!= INT_MAX && Mat[i][j] == 0 )//���ı��ʼʱ���еľ���?
				{
					dist[i][j] = dist[i][k]+dist[k][j] ;
				}
			}
		}
	}
}

int CalcAssi( int p , int **CopyCalc , int n , int ***AllPaths , int *RouteS )
{
	int v1 , v2 ; 
		for ( int j = 1 ; j < n ; j++ )
		{
			v1 = AllPaths[p][RouteS[p]][j] ;
			v2 = AllPaths[p][RouteS[p]][j+1] ;
			if ( v2 == -1 )break ;
			CopyCalc[v1][v2]++ ; 
		}
	int max = CopyCalc[0][0] ;
	for ( int i = 0 ; i < n ; i++ )
	{
		for ( int j = 0 ; j < n ; j++ )
		{
			if ( max <  CopyCalc[i][j] )
			{
				max = CopyCalc[i][j] ;
			}
		}
	}
	return max ;
}
void ValueCopy ( int **A , int **B , int n )
{
	for ( int i = 0 ; i < n ; i++ )
	{
		for ( int j = 0 ; j < n ; j++ )
		{
			A[i][j] = B[i][j] ;
		}
	}
}
bool DetectConfic( int *A , int *B , int **Calc)
{
	//�������·���Ƿ��г��?
	int v1 , v2 ;
	for ( int i = 1 ; i < A[0] ; i++ )
	{
		v1 = A[i];
		v2 = A[i+1] ;
		Calc[v1][v2]++ ;
	}
	for ( int i = 1 ; i < B[0] ; i++ )
	{
		v1 = B[i];
		v2 = B[i+1] ;
		Calc[v1][v2]++ ;
		if ( Calc[v1][v2] > 1 )
			return false ;
	}
	return true ;
}

void RWA::InitSolution()
{
	//װ���ʼ��?
	int i , j , k ;
	int v1 , v2 ; 
	//cout<<"InitSolution..."<<endl ;
	//̰���㷨��ʼ��ѡ·��
	int **Calc , **CopyCalc; 
	Calc = (int**)malloc(sizeof(int*)*N);
	CopyCalc = (int**)malloc(sizeof(int*)*N);
	for ( i = 0 ; i < N ; i++ )
	{
		Calc[i] = (int*)malloc(sizeof(int)*N);
		memset(Calc[i],0,sizeof(int)*N);
		CopyCalc[i] = (int*)malloc(sizeof(int)*N);
		memset(CopyCalc[i],0,sizeof(int)*N);
	}
	//string Filename("E:\\612\\personal\\yanshengfeng\\instances\\Y_Result\\");//Y.3.1.net
	//Filename = Filename+instancesname+".trf_result.txt";

	//string Filename("E:\\SVN\\BFD_RESULT\\z_rwa_result\\") ;
	string Filename("box_rwa_result\\") ;
	
	Filename = Filename+"Y.3.20.1.trf_result.txt";

	ifstream fin(Filename.c_str());
	 if ( fin.fail() )
     {
           cout << "### Erreur open, File_Name " << Filename << endl;
           exit(0);
     }
     if ( fin.eof() )
     {
           cout << "### Error open, File_Name " << Filename << endl;
           exit(0);
     }
	 string headline ;
	 getline(fin,headline);
	 getline(fin,headline);
	 int color ,lp;
	 Color = 0 ;
	 while(!fin.eof())
	 {
		fin>>lp>>color ;
		fin>>RouteS[lp][0] ;
		BestRouteS[lp][0] = RouteS[lp][0] ;
		BestColorS[lp] = ColorS[lp] = color ;
		//cout<<lp<<":"<<color<<" ";
		//��ʼ��Color
		Color = Color>color?Color:color ;
		//cout<<"lp="<<lp<<"Routelength="<<Route[lp-1][0]<<endl;
		for ( int i = 1 ; i <= RouteS[lp][0] ; i++ )
		{
			fin>>RouteS[lp][i] ;
			BestRouteS[lp][i] = RouteS[lp][i] ;
		}
	 }
	for ( i = 0 ; i < N ; i++ )
	{
		free(Calc[i]);
		free(CopyCalc[i]);
	}
	free(Calc);
	free(CopyCalc);

	//��ʼ��LIDC��
	LIDC = (int**)malloc(sizeof(int*)*(Color+1));
	BestLIDC = (int**)malloc(sizeof(int*)*(Color+1));
	for ( i = 0 ; i <= Color ; i++ )
	{
		LIDC[i] = (int*)malloc(sizeof(int*)*(LP+1));
		BestLIDC[i] = (int*)malloc(sizeof(int*)*(LP+1));
		memset(BestLIDC[i],-1,sizeof(int*)*(LP+1));
		memset(LIDC[i],-1,sizeof(int*)*(LP+1));
		LIDC[i][0] = 0 ;//�ڱ���¼ÿ����ɫ���е�lightpath��
		BestLIDC[i][0] = 0 ;
	}
	int num = 0 ;
	for ( i = 0 ; i < LP ; i++ )
	{
		num = LIDC[ColorS[i]][0] ;
		BestLIDC[ColorS[i]][num+1] = LIDC[ColorS[i]][num+1] = i ;
		LIDC[ColorS[i]][0]++ ;
		BestLIDC[ColorS[i]][0]++ ;
	}
	//��ɫ���ɱ�����ռ�?
	Tabu = (int*)malloc(sizeof(int)*LP);
	//TabuTenure2=(int**)malloc(sizeof(int*)*(LP)); //N��·���� 
	/*for ( i = 0 ; i <= LP ; i++ )
	{
		TabuTenure2[i]=(int*)malloc(sizeof(int*)*(Color));
		memset(TabuTenure2[i],0,sizeof(int*)*(Color));
	}*/
	memset(Tabu,-1,sizeof(int)*LP);
	//cout<<"End InitSolution"<<endl;
	for ( int i = 0 ; i < LP ; i++ )
		LPNum[i] = i ;
}

int RWA::Check()
{
	int **Ck , count = 0 ;
	Ck = (int**)malloc(sizeof(int*)*N);
	for (int i = 0 ; i < N ; i++ )
	{
		Ck[i] = (int*)malloc(sizeof(int)*N);
		//memset(Ck[i],0,sizeof(int)*N);
	}
	for ( int i = 0 ; i <= Color ; i++ )
	{
		count = 0 ;
		for (int g = 0 ; g < N ; g++ )
		{
			memset(Ck[g],0,sizeof(int)*N);
		}
		for ( int j = 1 ; j <= LIDC[i][0] ; j++ )
		{
			for ( int k = 1 ; k < RouteS[LIDC[i][j]][0] ; k++ )//AllPaths[j][RouteIndex[j]][0]
			{
				int v1 = RouteS[LIDC[i][j]][k] ;
				int v2 = RouteS[LIDC[i][j]][k+1] ;
				Ck[v1][v2]++ ;
				if ( Ck[v1][v2] > 1 )
				{
					count++ ; 
					return count ;
				}
			}
		}

	}
	for (int i = 0 ; i < N ; i++ )
	{
		free(Ck[i]);
	}
	free(Ck) ; 
	//cout<<"count of conflic = "<<count<<endl;
	return count ; 
}
void RWA::print()
{
	cout<<"��ǰ��ɫ��Ϊ "<<Color<<endl;
	cout<<"��ǰ�ܳ�ͻ��Ϊ "<<AllConflict<<endl;
}
void RWA::InitIncChart()
{
	int i,j,k;
	int v1,v2;

	//��ʼ����ǰ��ĳ�ͻ��?
	AllConflict = 0;
	memset(Conflict,0,sizeof(int)*LP);
	for ( i = 0 ; i < LP ; i++ )
	{
		memset(IncChart[i],0,sizeof(int)*Edge);
		memset(IncChartt[i],0,sizeof(int)*Edge);
		memset(IncChartCopy[i],0,sizeof(int)*Edge);
	}

	for(i=0;i<LP;i++)
	{
		for(j=i+1;j<LP;j++)//i+1
		{
			//����ɫ��ͬ���޸�������
			if(ColorS[i] == ColorS[j])
			{
				for(int m=1;m<RouteS[j][0];m++)
				{
					v1 = RouteS[j][m];
					v2 = RouteS[j][m+1];
					++IncChart[i][ChartMat[v1][v2]];
					IncChartt[i][ChartMat[v1][v2]]+=weight[i];
					++IncChartCopy[i][ChartMat[v1][v2]];
				}
				for(int n=1;n<RouteS[i][0];n++)
				{
					v1 = RouteS[i][n];
					v2 = RouteS[i][n+1];
					++IncChart[j][ChartMat[v1][v2]];
					IncChartt[j][ChartMat[v1][v2]]+=weight[i];
					++IncChartCopy[j][ChartMat[v1][v2]];
				}
			}
		}

		//�õ���ǰ��·�ĳ�ͻ��
		for(k=1;k<RouteS[i][0];k++)
		{
			v1 = RouteS[i][k];
			v2 = RouteS[i][k+1];
			Conflict[i] += IncChart[i][ChartMat[v1][v2]];
			weight[i]+=IncChartt[i][ChartMat[v1][v2]];
		}

		AllConflict += Conflict[i];
	}
}
void RWA::RecoverAndCopy( bool flag )
{
	if ( flag )//flagΪtrue���ǽ���ǰ�⸳ֵ��ȫ�����Ž�
	{
		//cout<<"flag == true "<<endl;
		for ( int i = 0 ; i < LP ; i++ )
		{
			memset(BestRouteS[i],-1,sizeof(int)*N);
			for ( int j = 0 ; j <= RouteS[i][0] ; j++ )
			{
				BestRouteS[i][j] = RouteS[i][j] ;
			}
			BestColorS[i] = ColorS[i] ;
			ConflictCopy[i] = Conflict[i] ;
		}
		for ( int i = 0 ; i <= Color ; i++ )
		{
			memset(BestLIDC[i],-1,sizeof(int*)*(LP+1));
			for ( int j = 0 ; j <= LIDC[i][0] ; j++ )
			{
				BestLIDC[i][j] = LIDC[i][j] ;
			}
		}
	}
	else //flagΪfalse���ǽ�ȫ�����Ž⸳ֵ����ǰ��
	{
		//cout<<"flag == false "<<endl;
		for ( int i = 0 ; i < LP ; i++ )
		{
			memset(RouteS[i],-1,sizeof(int)*N);
			for ( int j = 0 ; j <= BestRouteS[i][0] ; j++ )
			{
				RouteS[i][j] = BestRouteS[i][j] ;
			}
			ColorS[i] = BestColorS[i] ;
			Conflict[i] = ConflictCopy[i] ;
		}
		for ( int i = 0 ; i <= Color ; i++ )
		{
			memset(LIDC[i],-1,sizeof(int*)*(LP+1));
			for ( int j = 0 ; j <= BestLIDC[i][0] ; j++ )
			{
				LIDC[i][j] = BestLIDC[i][j] ;
			}
		}
	}
}
void RWA::LocalSearch()
{
	start = clock();
	int outvalue = AllConflict , count = 0 , perturbation = 0 , freq = 6 ;
	int chgpertur = 0 , minvalue = INT_MAX ;
	
	cout<<"AllConflict = "<<AllConflict/2<<"  Color = "<<Color+1<<endl;
	while ( true )
	{
		bool flag = ChangeColor();
		if ( flag )
		{
			outvalue = AllConflict ;
			//������ǰ������Ž�?
			RecoverAndCopy(true);
			minvalue = AllConflict ;
		}


		//MixChange(true);
		bool Rfg = ReplaceRoute();
		if ( Rfg )//&& perturbation <= 600 )
		{
			//perturbation++ ;
			if ( AllConflict < minvalue )
			{
				minvalue = AllConflict ;
				RecoverAndCopy(true);
			}
			continue ;
		}
		EjCRoute();
		if ( outvalue <= AllConflict )//outvalue <= AllConflict
		{	
			perturbation++ ;
			if ( AllConflict < minvalue )
			{
				minvalue = AllConflict ;
				RecoverAndCopy(true);
			}
		}
		else if ( outvalue > AllConflict )
		{
			perturbation = 0 ;
			outvalue = AllConflict ;
			if ( AllConflict < minvalue )
			{
				minvalue = AllConflict ;
				//������ǰ������Ž�?
				RecoverAndCopy(true);
			}
			cout<<"AllConflict = "<<AllConflict/2<<"  Color = "<<Color+1<<" minvalue = "<<minvalue/2<<endl;
		}
		float endtime = clock();
		/*if ( (endtime - start )/1000 >= 300 )
		{
			exit(0);
		}*/

		if (perturbation > 1000){
			perturbation = 0;
			printf("perturbation....\n");
			//Perturb(LP / 100 + 1);
			
			for (int i = 0; i <1; i++){
				Perturb_o(minvalue);
			}
			
			outvalue = AllConflict;
			cout << "AllConflict = " << AllConflict / 2 << "  Color = " << Color + 1 << " minvalue = " << minvalue / 2 << endl;
		}

		
	}
}

void RWA::Perturb_o(int minvalue){
	RecoverAndCopy(false);
	int chglp , exchglp , chgcolor, count , pos1 , pos2 ;
	memset(Tabu,-1,sizeof(int)*N);
	/*for ( i = 0 ; i <= LP ; i++ )
	{
		memset(TabuTenure2[i],0,sizeof(int*)*(Color));
	}*/
	int Tprob = minvalue>30?5:0 ;//�����Ŷ�ǿ��
	for ( int i = 0 ; i <= Color ; i++ )
	{
		if ( rand()%10 < Tprob )
			continue ;
		chglp = -1 ;count = 1 ;
		for ( int j = 1 ; j <= LIDC[i][0] ; j++ )
		{
			int lp = LIDC[i][j] ;
			if ( Conflict[lp] != 0 && rand()%(count) == 0 && Tabu[lp] == -1 )
			{
				chglp = lp ;
				pos1 = j ;
				count++ ;
			}
		}
		if ( chglp == -1 )
			continue ;
		do{
			chgcolor = rand()%(Color+1) ;
		}while(chgcolor==ColorS[chglp]||Tabu[chglp] == chgcolor );
		exchglp = -1 ;count = 1 ;
		for ( int j = 1 ; j <= LIDC[chgcolor][0] ; j++ )
		{
			int lp = LIDC[chgcolor][j] ;
			if ( Conflict[lp] != 0 && rand()%(count++) == 0 )
			{
				exchglp = lp ;
				pos2 = j ;
			}
		}
		if ( exchglp == -1 )
		{//û���ҵ�������lp�������?
			int t = LIDC[ColorS[chglp]][0] ;
			LIDC[ColorS[chglp]][pos1] = LIDC[ColorS[chglp]][t] ;
			LIDC[ColorS[chglp]][t] = -1 ;
			LIDC[ColorS[chglp]][0]-- ;
			int num = ++LIDC[chgcolor][0] ;
			LIDC[chgcolor][num] = chglp ;
			ColorS[chglp] = chgcolor ;
		}
		else 
		{//�ҵ�������lp����н���?
			LIDC[ColorS[chglp]][pos1] = exchglp ;
			LIDC[chgcolor][pos2] = chglp ;
			ColorS[exchglp] = ColorS[chglp] ;
			ColorS[chglp] = chgcolor ;
			Tabu[exchglp] = chgcolor ;
		}
		Tabu[chglp] = i ;
	}
	InitIncChart();
	MixChange(false);
	//Fetch_Insert();

	int iter=0;		
	/*if ( AllConflict < minvalue )//����tabu2�Ľ��ɱ�
	{
		minvalue = AllConflict ;
		RecoverAndCopy(true);
		for (int i=0;i<LP;i++)
		{
			for (int j=0;j<Color;j++)
			{
				if( TabuTenure2[ i ][ j ] <= iter )
				{
					
					TabuTenure2[ tabu_best_x[ select ] ][ old_color ] = rand( ) % 10 + 2 + f ;  
					iter ++ ;
				}
			}
		}

	}*/
}

void RWA::Perturb(int strength){
	int lp_Index;
	int lp_Color;
	RecoverAndCopy(false);
	memset(Tabu, -1, sizeof(int)*N);
	for (int i = 0; i < strength; i++){
		lp_Index = rand() % LP;
		lp_Color = rand() % (Color + 1);
		ColorS[lp_Index] = lp_Color;
	}

	for (int i = 0; i <= Color; i++){
		memset(LIDC[i], -1, sizeof(int*)*(LP + 1));
		LIDC[i][0] = 0;//�ڱ���¼ÿ����ɫ���е�lightpath��
	}
	int num = 0;
	for (int i = 0; i < LP; i++){
		num = LIDC[ColorS[i]][0];
		LIDC[ColorS[i]][num + 1] = i;
		LIDC[ColorS[i]][0]++;
	}

	InitIncChart();
}


bool RWA::FindShortRoute( )
{
	//cout<<"enter FindShortRoute"<<endl;
	int D , S , L ;
	int *R = NULL ;
	bool flag = false ;
	for ( int i = 0 ; i < LP ; i++ )
	{
		if ( Conflict[i] != 0 )
			continue ;
		L = RouteS[i][0] ;
		S = RouteS[i][1] ;
		D = RouteS[i][L] ;
		if ( L*1.0/dist[S][D] > 1.5 )
		{
			//·����Գ��Ƚϴ��������?
			R = NULL ; 
			R = Pseudo_DFS(i);
			if ( R != NULL && R[0] < L )
			{
				UpdataRoute(i,R);
				flag = true ;
				cout<<"# find a new route #"<<endl;
				exit(0);
			}
		}
	}
	return flag ;
}

void RWA::MixChange(bool flag)
{
	int color=0 , *R , count , max = 0  ;
	color = rand()%(Color+1) ;
	int length = LIDC[color][0] ;
	vector<int> MyVec ;
	for ( int i = 0 ; i <= Color ; i++ )
		MyVec.push_back(i);
	std::random_shuffle(MyVec.begin(),MyVec.end());
	for ( int i = 1 ; i <= length && AllConflict != 0 ; i++ )
	{
		int lp = LIDC[color][i] ;
		for ( int k = 0 ; k < MyVec.size() ; k++ )
		{
			int j = MyVec[k];
			R = NULL ;
			if ( j == color )
				continue ;
			ColorS[lp] = j ;
			if(!flag)
				R = Pseudo_DFS(lp,Conflict[lp]) ;//Conflict[lp]
			else
				R = Pseudo_DFS(lp,0);
			ColorS[lp] = color ;
			if ( R == NULL )
				continue ;
			UpdataMixChg(lp,j,R);
			length = LIDC[color][0] ;
			i-- ;
			Tabu[lp] = -1 ; 
			break;
		}
	}
	MyVec.clear();
}
void RWA::UpdataMixChg( int chglp , int chgcolor , int* RT )
{
	int precolor = ColorS[chglp] , pos ;
	//�ı�IncChart
	for ( int i = 1 ; i <= LIDC[precolor][0] ; i++ )
	{
		int lp = LIDC[precolor][i] ;
		if ( lp == chglp )
		{
			pos = i ;
			continue ;
		} 
		AllConflict -= Conflict[lp];
		Conflict[lp] = 0 ;
		for ( int j = 1 ; j < RouteS[chglp][0] ; j++ )
		{
			int v1 = RouteS[chglp][j] ;
			int v2 = RouteS[chglp][j+1] ;
			int pos = ChartMat[v1][v2];
			IncChart[lp][pos]-- ;
			IncChartt[lp][pos]-=weight[lp] ;
			IncChartCopy[lp][pos] = IncChart[lp][pos] ;
		}
		for ( int j = 1 ; j < RouteS[lp][0] ; j++ )
		{
			int v1 = RouteS[lp][j] ;
			int v2 = RouteS[lp][j+1] ;
			int pos = ChartMat[v1][v2];
			Conflict[lp] += IncChart[lp][pos] ;
			weight[lp]+=IncChartt[lp][pos];
		}
		AllConflict += Conflict[lp] ;
	}
	int num = LIDC[precolor][0] ; 
	LIDC[precolor][pos] = LIDC[precolor][num] ;
	LIDC[precolor][num] = -1 ; 
	LIDC[precolor][0]-- ;
	//�任��·
	int length = RouteS[chglp][0]>RT[0]?RouteS[chglp][0]:RT[0] ;
	for ( int i = 0 ; i <= length ; i++ )
	{
		RouteS[chglp][i] = RT[i] ;
	}
	//�ı�������
	memset(IncChart[chglp],0,sizeof(int)*Edge);
	memset(IncChartt[chglp],0,sizeof(int)*Edge);
	for( int i = 1 ; i <= LIDC[chgcolor][0] ; i++ )
	{
		int lp = LIDC[chgcolor][i] ;
		AllConflict -= Conflict[lp];
		Conflict[lp] = 0 ;
		for ( int j = 1 ; j < RouteS[chglp][0] ; j++ )
		{
			int v1 = RouteS[chglp][j] ;
			int v2 = RouteS[chglp][j+1] ;
			int pos = ChartMat[v1][v2];
			IncChart[lp][pos]++ ;
			IncChartt[lp][pos]+=weight[lp] ;
			IncChartCopy[lp][pos] = IncChart[lp][pos] ;
		}
		for ( int j = 1 ; j < RouteS[lp][0] ; j++ )
		{
			int v1 = RouteS[lp][j] ;
			int v2 = RouteS[lp][j+1] ;
			int pos = ChartMat[v1][v2];
			Conflict[lp] += IncChart[lp][pos] ;
			weight[lp]+=IncChartt[lp][pos];
		}
		AllConflict += Conflict[lp] ;
		for ( int j = 1 ; j < RouteS[lp][0] ; j++ )
		{
			int v1 = RouteS[lp][j] ;
			int v2 = RouteS[lp][j+1] ;
			int pos = ChartMat[v1][v2];
			IncChart[chglp][pos]++ ;
			IncChartt[chglp][pos]+=weight[chglp] ;
			IncChartCopy[chglp][pos] = IncChart[chglp][pos] ;
		}
	}
	AllConflict -= Conflict[chglp];
	Conflict[chglp] = 0 ;
	for ( int i = 1 ; i < RouteS[chglp][0] ; i++ )
	{
		int v1 = RouteS[chglp][i] ;
		int v2 = RouteS[chglp][i+1] ;
		int pos = ChartMat[v1][v2];
		Conflict[chglp] += IncChart[chglp][pos] ;
		weight[chglp]+=IncChartt[chglp][pos];
	}
	AllConflict += Conflict[chglp];
	//chglp���뵽chgcolor��
	num = ++LIDC[chgcolor][0] ;
	LIDC[chgcolor][num] = chglp ;
	ColorS[chglp] = chgcolor ;
}

bool RWA::ReplaceRoute()
{
	int *R = NULL ;
	int oldvalue = AllConflict ;
	bool flag = true  ;
	int value , minvalue = INT_MAX, minlp = -1 ,EqProb = 1 ;
	memset(BR,-1,sizeof(int)*N);//�������·��?
	for ( int i = 0 ; i < LP && AllConflict!=0 ; i++ )
	{
		if ( Conflict[i] == 0 )
			continue ;
		R = Pseudo_BFS(i);/*,Conflict[i]*/
		if ( R == NULL )
			continue ;
		value = Estimation(i,R) ;//���㻻·֮��ĳ�ͻ��?
		if ( value < minvalue )
		{
			minvalue = value ;
			minlp = i ;
			int len = R[0] > BR[0] ?R[0]:BR[0] ;
			for ( int k = 0 ; k <= len ; k++ )//������·���⻻ΪR
			{
				BR[k] = R[k] ;
			}
			EqProb = 1 ;
		}
		else if ( value == minvalue && rand()%(++EqProb) == 0 )//�ȸ��ʽ���Ч����ͬ�Ľ�
		{
			minlp = i ;
			int len = R[0] > BR[0] ?R[0]:BR[0] ;
			for ( int k = 0 ; k <= len ; k++ )//������·���⻻ΪR
			{
				BR[k] = R[k] ;
			}
		}
		R = NULL ; 
	}
	if ( minlp > 0 )//�����õ���Ч����õĹ�·��BR����
	{
		UpdataRoute(minlp,BR);
		Tabu[minlp] = -1 ;//���?
	}
	if ( AllConflict < oldvalue )//��·�ɹ�
		return true ;
	return false ;
}
int RWA::Estimation( int lp , int* R )
{
	int value = 0 ;
	for ( int i = 1 ; i < R[0] ; i++ )
	{
		int v1 = R[i] ;
		int v2 = R[i+1] ;
		value += IncChart[lp][ChartMat[v1][v2]] ;
	}
	return (value-Conflict[lp]) ;
}
void RWA::UpdataRoute( int lp , int *R )
{
	//��RouteS��¼��ʵ��·��
	int color = ColorS[lp] ;
	int v1 , v2 , position ;
	memset(IncChart[lp],0,sizeof(int)*Edge);
	memset(IncChartt[lp],0,sizeof(int)*Edge);
	AllConflict -= Conflict[lp] ;
	Conflict[lp] = 0 ;
	int length = LIDC[color][0] ;
	for ( int i = 1 ; i <= length ; i++ )
	{
		int temp = LIDC[color][i] ;
		if ( temp == lp )
			continue ;
		AllConflict -= Conflict[temp] ;
		for ( int j = 1 ; j < RouteS[lp][0] ; j++ )
		{
			v1 = RouteS[lp][j] ;
			v2 = RouteS[lp][j+1] ;
			position = ChartMat[v1][v2] ;
			IncChart[temp][position]--;
			IncChartt[temp][position]-=weight[temp];
			IncChartCopy[temp][position] = IncChart[temp][position] ;
		}
		for ( int h = 1 ; h < R[0] ; h++ )
		{
			v1 = R[h] ;
			v2 = R[h+1] ;
			position = ChartMat[v1][v2] ;
			IncChart[temp][position]++ ;
			IncChartt[temp][position]+=weight[temp] ;
			IncChartCopy[temp][position] = IncChart[temp][position] ;
		}
		Conflict[temp] = 0 ; 
		for ( int k = 1 ; k < RouteS[temp][0] ; k++ )
		{
			v1 = RouteS[temp][k] ;
			v2 = RouteS[temp][k+1] ;
			position = ChartMat[v1][v2] ;
			IncChart[lp][position]++ ;
			IncChartt[lp][position]+=weight[lp] ;
			IncChartCopy[lp][position] = IncChart[lp][position] ;
			Conflict[temp] += IncChart[temp][position] ;
			weight[temp]+=IncChartt[temp][position];
		}
		AllConflict += Conflict[temp] ;
	}
	for ( int p = 1 ; p < R[0] ; p++ )
	{
		v1 = R[p] ;
		v2 = R[p+1] ;
		position = ChartMat[v1][v2] ;
		Conflict[lp] += IncChart[lp][position] ;
		weight[lp]+=IncChartt[lp][position];
	}
	AllConflict += Conflict[lp] ;

	int  nc ;
	for( nc = 1 ; nc <= R[0] ; nc++ )
	{
		RouteS[lp][nc] = R[nc] ;
	}
	for ( int cp = nc+1 ; cp <= RouteS[lp][0] ; cp++ )
	{
		RouteS[lp][cp] = -1 ;
	}
	RouteS[lp][0] = R[0] ;
}

//*����Ejection chain��·����*/
void RWA::EjCRoute()
{
	std::random_shuffle(LPNum,LPNum+LP);//��LPNum�����������?
	int Chglp = -1 ;
	//�ҳ���Ҫ����lightpath
	for ( int i = 0 ; i < LP ; i++ )
	{
		int clp = LPNum[i] ;//������ҳ�һ���г�ͻ�Ĺ�·Chglp
		if ( Conflict[clp] != 0 )
		{
			Chglp = clp ;
			break;
		}
	}
	if ( Chglp == -1 )//��ȫ���޳�ֱ���˳�
		return ;
	int CurrColor = ColorS[Chglp];//Chglp����ɫΪCurrColor
	ColorS[Chglp] = -1 ;
	AllConflict -= Conflict[Chglp];
	//����·����ɫ�����޳�/��ȡ
	int v1 , v2 , pos = -1 ;
	for ( int i = 1 ; i <= LIDC[CurrColor][0] ; i++ )
	{
		int lp = LIDC[CurrColor][i] ;//ȡ��ÿһ��ʹ�õ�ǰ��ɫ��·��
		if ( lp == Chglp )
		{
			pos = i ;
			continue ;
		}
		for ( int j = 1 ; j < RouteS[Chglp][0] ; j++ )//��·��lp���Ǵ�����·��Chglpʱ������Chglp·���ϵ�ÿһ����
		{
			v1 = RouteS[Chglp][j] ;
			v2 = RouteS[Chglp][j+1] ;
			int position = ChartMat[v1][v2];
			IncChart[lp][position]-- ;//��lp·���϶�Ӧ�ı߿�ȥ
			IncChartt[lp][position]-=weight[lp] ;
			IncChartCopy[lp][position] = IncChart[lp][position] ;
			if ( IncChart[lp][position] < 0 )
			{
				cout<<" С��0�ļ����� ! "<<endl;
				exit(0);
			}
		}
		AllConflict -= Conflict[lp];
		Conflict[lp] = 0 ;
		for ( int j = 1 ; j < RouteS[lp][0] ; j++ )//���¼���lp�ĳ�ͻ
		{
			v1 = RouteS[lp][j] ; 
			v2 = RouteS[lp][j+1] ;
			int position = ChartMat[v1][v2];
			Conflict[lp] += IncChart[lp][position];
			weight[lp]+=IncChartt[lp][position];
		}
		AllConflict += Conflict[lp];
	}
	//��LIDC����ȥ��
	if ( pos == -1 )
	{
		cout <<"��ʽ��·����!!"<<endl;
		exit(0);
	}
	int num = LIDC[CurrColor][0] ;
	LIDC[CurrColor][pos] = LIDC[CurrColor][num] ;
	LIDC[CurrColor][num] = -1 ;
	LIDC[CurrColor][0]-- ;//��ʱChglp�Ͳ���CurrColorȾɫ��
	//�������޳�ͻ���뵽CurrColor��ɫ���е�Lightpath
	bool flag = true ;
	int CandColor , *R = NULL ;
	while ( flag )
	{
		flag = false ;
		for ( int i = 0 ; i < LP ; i++ )
		{
			int lp = LPNum[i] ;
			if ( lp == Chglp || Conflict[lp] == 0 )
				continue ;
			CandColor = ColorS[lp] ;
			R = NULL ;
			ColorS[lp] = CurrColor ;
			R = Pseudo_DFS(lp,0);
			ColorS[lp] = CandColor ;
			if ( R != NULL )
			{
				flag = true ;
				//cout<<"find a new route"<<endl;
				UpdataMixChg(lp,CurrColor,R);
				CurrColor = CandColor ;
				Tabu[lp] = -1 ;
				break ;
			}
		}
	}
	//��Chglp���뵽���һ�����������κ�lightpath����ɫ����
	InsetRoute(Chglp,CurrColor);
	Tabu[Chglp] = -1 ;
}
void RWA::InsetRoute( int Clp , int Cr )//��Clp��·Ϊʹ��Cr�ĵ�һ����·
{
	memset(IncChart[Clp],0,sizeof(int)*Edge);
	memset(IncChartt[Clp],0,sizeof(int)*Edge);
	int v1 , v2 ;
	if ( LIDC[Cr][0] != 0 )
	{
		int lp = LIDC[Cr][1] ;
		for ( int i = 0 ; i < Edge ; i++ )
		{
			IncChart[Clp][i] = IncChart[lp][i] ;
			IncChartt[Clp][i] = IncChartt[lp][i] ;
		}
		for ( int j = 1 ; j < RouteS[lp][0] ; j++ )
		{
			v1 = RouteS[lp][j] ;
			v2 = RouteS[lp][j+1] ;
			int position = ChartMat[v1][v2];
			IncChart[Clp][position]++ ;
			IncChartt[Clp][position]+=weight[Clp] ;
			IncChartCopy[Clp][position] = IncChart[Clp][position] ;
		}

		Conflict[Clp] = 0 ;
		for ( int j = 1 ; j < RouteS[Clp][0] ; j++ )
		{
			v1 = RouteS[Clp][j] ;
			v2 = RouteS[Clp][j+1] ;
			int position = ChartMat[v1][v2];
			Conflict[Clp] += IncChart[Clp][position] ;
			weight[Clp] += IncChartt[Clp][position] ;
		}
		AllConflict += Conflict[Clp];
	}
	for( int i = 1 ; i <= LIDC[Cr][0] ; i++ )
	{
		int lp = LIDC[Cr][i] ;
		for ( int j = 1 ; j < RouteS[Clp][0] ; j++ )
		{
			v1 = RouteS[Clp][j] ;
			v2 = RouteS[Clp][j+1] ;
			int position = ChartMat[v1][v2];
			IncChart[lp][position]++ ;
			IncChartt[lp][position]+=weight[lp] ;
			IncChartCopy[lp][position] = IncChart[lp][position] ;
		}
		AllConflict -= Conflict[lp];
		Conflict[lp] = 0 ;
		for ( int j = 1 ; j < RouteS[lp][0] ; j++ )
		{
			v1 = RouteS[lp][j] ; 
			v2 = RouteS[lp][j+1] ;
			int position = ChartMat[v1][v2];
			Conflict[lp] += IncChart[lp][position];
			weight[lp]+=IncChartt[lp][position];
		}
		AllConflict += Conflict[lp];

		/*for ( int j = 1 ; j < RouteS[lp][0] ; j++ )
		{
			v1 = RouteS[lp][j] ;
			v2 = RouteS[lp][j+1] ;
			int position = ChartMat[v1][v2];
			IncChart[Clp][position]++ ;
			IncChartCopy[Clp][position] = IncChart[Clp][position] ;
		}*/
	}
	//Conflict[Clp] = 0 ;
	//for ( int j = 1 ; j < RouteS[Clp][0] ; j++ )
	//{
	//	v1 = RouteS[Clp][j] ;
	//	v2 = RouteS[Clp][j+1] ;
	//	int position = ChartMat[v1][v2];
	//	Conflict[Clp] += IncChart[Clp][position] ;
	//}
	//AllConflict += Conflict[Clp];
	int num = ++LIDC[Cr][0] ;
	LIDC[Cr][num] = Clp ;
	ColorS[Clp] = Cr ;

	/*AllConflict = 0 ;
	for ( int i = 0 ; i < LP ; i++ )
	{
		AllConflict += Conflict[i] ;
	}*/
}

//*��ȡ�����뻻·����*/
void RWA::Fetch_Insert()
{
	//vector<int> DFLP ;//��¼���ܲ����lightpath
	std::random_shuffle(LPNum,LPNum+LP);
	int *R = NULL ;
	for ( int i = 0 ; i < LP ; i++ )
	{
		int lp = LPNum[i];
		if ( Conflict[lp] == 0 )
			continue ;
		Fetch_Lp(lp);
		Inset_Lp(lp);
		if ( ColorS[lp] == -1 )
		{
			DFLP.push_back(lp);
		}
	}
	//���Խ�֮ǰ��ȡ������lightpath���뵽��ɫ����
	//cout<<"number of Fetch :"<<DFLP.size()<<endl;
	vector<int>::iterator itr = DFLP.begin() ;
	while ( itr != DFLP.end() )
	{
		int lp = *itr ;
		Inset_Lp(lp);
		if ( ColorS[lp] == -1 )
		{
			int color = rand()%(Color+1) ;
			InsetRoute(lp,color);
		}
		//itr = DFLP.erase(itr);
		itr++ ;
	}
	//cout<<"after inset number of Fetch :"<<DFLP.size()<<endl;
	DFLP.clear() ;
}
void RWA::Fetch_Lp(int Chglp)
{
	int CurrColor = ColorS[Chglp];
	ColorS[Chglp] = -1 ;
	AllConflict -= Conflict[Chglp];
	//�ӵ�ǰ��ɫ����ȡ����
	int v1 , v2 , pos = -1 ;
	for ( int i = 1 ; i <= LIDC[CurrColor][0] ; i++ )
	{
		int lp = LIDC[CurrColor][i] ;
		if ( lp == Chglp )
		{
			pos = i ;
			continue ;
		}
		for ( int j = 1 ; j < RouteS[Chglp][0] ; j++ )
		{
			v1 = RouteS[Chglp][j] ;
			v2 = RouteS[Chglp][j+1] ;
			int position = ChartMat[v1][v2];
			IncChart[lp][position]-- ;
			IncChartt[lp][position]-=weight[lp] ;
			IncChartCopy[lp][position] = IncChart[lp][position] ;
			if ( IncChart[lp][position] < 0 )
			{
				cout<<" С��0�ļ����� ! "<<endl;
				exit(0);
			}
		}
		AllConflict -= Conflict[lp];
		Conflict[lp] = 0 ;
		for ( int j = 1 ; j < RouteS[lp][0] ; j++ )
		{
			v1 = RouteS[lp][j] ; 
			v2 = RouteS[lp][j+1] ;
			int position = ChartMat[v1][v2];
			Conflict[lp] += IncChart[lp][position];
			weight[lp] += IncChartt[lp][position];
		}
		AllConflict += Conflict[lp];
	}
	//��LIDC����ȥ��
	if ( pos == -1 )
	{
		cout <<"��ʽ��·����!!"<<endl;
		exit(0);
	}
	int num = LIDC[CurrColor][0] ;
	LIDC[CurrColor][pos] = LIDC[CurrColor][num] ;
	LIDC[CurrColor][num] = -1 ;
	LIDC[CurrColor][0]-- ;
}
void RWA::Inset_Lp(int Chglp)
{
	int *R = NULL ;
	for ( int k = 0 ; k <= Color ; k++ )
	{
		ColorS[Chglp] = k ;
		R = NULL ;
		R = Pseudo_DFS(Chglp,0);
		ColorS[Chglp] = -1 ;
		if ( R != NULL )
		{
			UpdataInset(Chglp,k,R);
			Tabu[Chglp] = -1 ;
			return ;
		}
	}
}
void RWA::UpdataInset( int chglp , int chgcolor , int* RT )
{
	//�任��·
	int length = RouteS[chglp][0]>RT[0]?RouteS[chglp][0]:RT[0] ;
	for ( int i = 0 ; i <= length ; i++ )
	{
		RouteS[chglp][i] = RT[i] ;
	}
	//�ı�������
	memset(IncChart[chglp],0,sizeof(int)*Edge);
	memset(IncChartt[chglp],0,sizeof(int)*Edge);
	for( int i = 1 ; i <= LIDC[chgcolor][0] ; i++ )
	{
		int lp = LIDC[chgcolor][i] ;
		AllConflict -= Conflict[lp];
		Conflict[lp] = 0 ;
		for ( int j = 1 ; j < RouteS[chglp][0] ; j++ )
		{
			int v1 = RouteS[chglp][j] ;
			int v2 = RouteS[chglp][j+1] ;
			int pos = ChartMat[v1][v2];
			IncChart[lp][pos]++ ;
			IncChartt[lp][pos]+=weight[lp] ;
			IncChartCopy[lp][pos] = IncChart[lp][pos] ;
		}
		for ( int j = 1 ; j < RouteS[lp][0] ; j++ )
		{
			int v1 = RouteS[lp][j] ;
			int v2 = RouteS[lp][j+1] ;
			int pos = ChartMat[v1][v2];
			Conflict[lp] += IncChart[lp][pos] ;
			weight[lp] += IncChartt[lp][pos] ;
		}
		AllConflict += Conflict[lp] ;
		for ( int j = 1 ; j < RouteS[lp][0] ; j++ )
		{
			int v1 = RouteS[lp][j] ;
			int v2 = RouteS[lp][j+1] ;
			int pos = ChartMat[v1][v2];
			IncChart[chglp][pos]++ ;
			IncChartt[chglp][pos]+=weight[chglp] ;
			IncChartCopy[chglp][pos] = IncChart[chglp][pos] ;
		}
	}
	AllConflict -= Conflict[chglp];
	Conflict[chglp] = 0 ;
	for ( int i = 1 ; i < RouteS[chglp][0] ; i++ )
	{
		int v1 = RouteS[chglp][i] ;
		int v2 = RouteS[chglp][i+1] ;
		int pos = ChartMat[v1][v2];
		Conflict[chglp] += IncChart[chglp][pos] ;
		weight[chglp] += IncChartt[chglp][pos] ;
	}
	AllConflict += Conflict[chglp];
	//chglp���뵽chgcolor��
	int num = ++LIDC[chgcolor][0] ;
	LIDC[chgcolor][num] = chglp ;
	ColorS[chglp] = chgcolor ;
}

//*������ɫ*/
void RWA::ExChgColor()
{
	std::random_shuffle(LPNum,LPNum+LP);
	int Chglp = -1  , ChgColor;
	//�ҳ���Ҫ����lightpath
	for ( int i = 0 ; i < LP ; i++ )
	{
		int clp = LPNum[i] ;
		if ( Conflict[clp] != 0 )
		{
			Chglp = clp ;
			break;
		}
	}
	if ( Chglp != -1 )
	{
		int minvalue = 0 , value1 , value2 , Exclp ;
		memset(loc,0,sizeof(int)*Edge);
		for(int k = 1; k < RouteS[Chglp][0]; ++k)
		{
			int v1 = RouteS[Chglp][k];
			int v2 = RouteS[Chglp][k+1];
			loc[ChartMat[v1][v2]] = 1;
		}
		//�ҳ�һ������������С�Ľ�����
		int Scount = 1 ;
		for ( int i = 0 ; i < LP ; i++ )
		{
			int clp = LPNum[i] ;
			if ( Conflict[clp] == 0 || ColorS[clp] == ColorS[Chglp] )//Ҳ�����޳�ͻ��lightpath����
				continue ;
			value1 = EstimationOfChgColor(Chglp,ColorS[clp]);
			value2 = EstimationOfChgColor(clp,ColorS[Chglp]);
			int subvalue = 0 ;
			for ( int j = 1 ; j < RouteS[clp][0] ; j++ )
			{
				int v1 = RouteS[clp][j];
				int v2 = RouteS[clp][j];
				if(loc[ChartMat[v1][v2]] == 1)
					subvalue = subvalue + 4;
			}
			int sumvalue = value1+value2-subvalue ;
			if ( sumvalue < minvalue )
			{
				Exclp = clp ;
				minvalue = sumvalue ;
				Scount = 1 ;
			}
			else if ( sumvalue == minvalue && rand()%(++Scount) == 0 )
			{
				Exclp = clp ;
			}
		}
		//Chglp��Exclp������ɫ
		if ( minvalue < 0 ) 
		{
			UpdataExChgCor(Chglp,Exclp);
			UpdataExChgCor(Exclp,Chglp);
		}
	}
}
void RWA::UpdataExChgCor(int chglp , int exclp )
{
	UpdataIncChart(chglp,ColorS[exclp]);
	UpdataIncChart(exclp,ColorS[chglp]);
}

bool RWA::ChangeColor()//�ı���ɫ
{

	int iteration = 0 , jug ;
	bool flag = false , iflag = false ;
	if ( AllConflict == 0 )//Ŀ�꺯������0�����һ�����?  
	{
		cout<<"AllConflict = 0 "<<endl;
		iflag = true ;
		RecordFile();
		SubColor();
		memset(Tabu,-1,sizeof(int)*LP) ;
		iteration = 0 ; 
	}
	int ChgLp = 0 , ChgColor = ColorS[0] ;//Ҫ�ı��LightPath����ɫ,��ʼֵΪ0������ɫ
	int MinValue = INT_MAX , CurrentValue ;//AllConflict
	int EqProb = 1 ;
	//ÿ�λ���һ��lightpath�任��������ɫ/LIDCͬʱ��
	for ( int i = 0 ; i < LP ; i++ )
	{
		// bool nflag=0;
		// int v1,v2;
		// vector<int> cl;
		// cl.push_back(ColorS[i]);
		// for (int t=1;t< RouteS[i][0];t++)
		// {
		// 	v1=RouteS[i][t];
		// 	v2=RouteS[i][t+1];
		// 	int v1_a,v2_a;
		// 	for (int j=i+1;j<LP;j++)
		// 	{
		// 		for (int j2=1;j2<RouteS[j][0];j2++)
		// 		{
		// 			v1_a=RouteS[j][j2];
		// 			v2_a=RouteS[j][j2+1];
		// 			if (v1_a==v1&&v2_a==v2)
		// 			{
		// 				bool flag_a=0;
		// 				for (int bl=0;bl<cl.size();bl++)
		// 				{
		// 					if (cl[bl]==ColorS[j])
		// 					{
		// 						flag_a=1;
		// 						nflag=1;
		// 						break;
		// 					}
		// 				}
		// 				if (flag_a==0)
		// 				{
		// 					cl.push_back(ColorS[j]);
		// 				}
		// 				break;
		// 			}
		// 		}
		// 	}
		// }
		// if (nflag==1)
		// {
		// 	Chglp=i;
		// 	//����Ejroute
		// 	int CurrColor = ColorS[Chglp];//Chglp����ɫΪCurrColor
		// 	ColorS[Chglp] = -1 ;
		// 	AllConflict -= Conflict[Chglp];
		// 	//����·����ɫ�����޳�/��ȡ
		// 	int v1 , v2 , pos = -1 ;
		// 	for ( int i = 1 ; i <= LIDC[CurrColor][0] ; i++ )
		// 	{
		// 		int lp = LIDC[CurrColor][i] ;//ȡ��ÿһ��ʹ�õ�ǰ��ɫ��·��
		// 		if ( lp == Chglp )
		// 		{
		// 			pos = i ;
		// 			continue ;
		// 		}
		// 		for ( int j = 1 ; j < RouteS[Chglp][0] ; j++ )//��·��lp���Ǵ�����·��Chglpʱ������Chglp·���ϵ�ÿһ����
		// 		{
		// 			v1 = RouteS[Chglp][j] ;
		// 			v2 = RouteS[Chglp][j+1] ;
		// 			int position = ChartMat[v1][v2];
		// 			IncChart[lp][position]-- ;//��lp·���϶�Ӧ�ı߿�ȥ
		// 			IncChartCopy[lp][position] = IncChart[lp][position] ;
		// 			if ( IncChart[lp][position] < 0 )
		// 			{
		// 				cout<<" С��0�ļ����� ! "<<endl;
		// 				exit(0);
		// 			}
		// 		}
		// 		AllConflict -= Conflict[lp];
		// 		Conflict[lp] = 0 ;
		// 		for ( int j = 1 ; j < RouteS[lp][0] ; j++ )//���¼���lp�ĳ�ͻ
		// 		{
		// 			v1 = RouteS[lp][j] ; 
		// 			v2 = RouteS[lp][j+1] ;
		// 			int position = ChartMat[v1][v2];
		// 			Conflict[lp] += IncChart[lp][position];
		// 		}
		// 		AllConflict += Conflict[lp];
		// 	}
		// 	//��LIDC����ȥ��
		// 	if ( pos == -1 )
		// 	{
		// 		cout <<"��ʽ��·����!!"<<endl;
		// 		exit(0);
		// 	}
		// 	int num = LIDC[CurrColor][0] ;
		// 	LIDC[CurrColor][pos] = LIDC[CurrColor][num] ;
		// 	LIDC[CurrColor][num] = -1 ;
		// 	LIDC[CurrColor][0]-- ;
		// 	continue;
		// }


		int max_num=0;
		int max_loc;
		for (int m=i;m<LP;m++)
		{
			if(weight[m]>max_num)
			{
				max_num=weight[m];
				max_loc=m;
			}
		}
		int temp=i;
		i=max_loc;
		if ( Conflict[i] == 0 )//û�г�ͻ
			continue ;
		/*estimatetion׼������*/
		memset(loc,0,sizeof(int)*Edge);
		for(int k = 1; k < RouteS[i][0]; ++k)//��λһ����·�ϵ�����������
		{
			int v1 = RouteS[i][k];
			int v2 = RouteS[i][k+1];
			loc[ChartMat[v1][v2]] = 1;//loc�ϸù�·���������ϵ�ֵȫ��Ϊ1
		}
		for ( int j = 0 ; j <= Color ; j++ )
		{
			if( ColorS[i] == j || Tabu[i] != -1 )
			{
				Tabu[i] = -1 ;//����ǰ��·���?
				continue ;
			}
			CurrentValue = EstimationOfChgColor(i , j) ;//�����ǳ��Խ���ǰ��·��Ϊ��ǰ��ɫ

			if ( MinValue > CurrentValue ) //�����˱ȵ�ǰ��Ҫ��Ľ�?
			{
				ChgLp = i ; 
				ChgColor = j ;
				MinValue = CurrentValue ;
				flag = true ;
				EqProb = 1 ;
			}
			else if ( MinValue == CurrentValue && rand()%(++EqProb)==0 )//�ȸ��ʽ���ͬ��ֵ�Ľ�
			{
				ChgLp = i ; 
				ChgColor = j ;
				flag = true ;
			}
		}
		i=temp;
	}
	if ( flag )
	{
		jug = AllConflict ;
		Tabu[ChgLp] = ColorS[ChgLp] ;
		UpdataIncChart(ChgLp , ChgColor);
	}
	return iflag ;
}
void RWA::SubColor()
{
	//̰�ķ�������
	int min = INT_MAX , mincolor ;
	float end = clock() ;
	for ( int i = 0 ; i <= Color ; i++ )
	{
		if ( min > LIDC[i][0] )
		{
			min = LIDC[i][0] ;
			mincolor = i ;
		}
	}
	/*��LIDC[mincolor]�е�Ԫ�س��Ƚ��зǵ�������*/
	bool flag ;
	vector<int> sort ;
	sort.push_back(LIDC[mincolor][1]);
	for ( int i = 2 ; i <= LIDC[mincolor][0] ; i++ )
	{
		int lp = LIDC[mincolor][i] ;
		flag = false ;
		for ( int j = 0 ; j < sort.size() ; j++ )
		{
			int len = RouteS[sort[j]][0] ;
			if ( RouteS[lp][0] > len )
			{
				sort.insert(sort.begin()+j,lp);
				flag = true ;
				break;
			}
		}
		if ( !flag )
			sort.push_back(lp);
	}

	int minnum = LIDC[mincolor][0] ;
	int value , minvalue , chglp , chgcolor ,num ;
	for ( int i = 1 ; i <= minnum ; i++ )//vector<int>::size_type 
	{
		//chglp = sort[i] ;//LIDC[mincolor][i] ;
		chglp = LIDC[mincolor][i] ;
		minvalue = INT_MAX ;
		/*estimatetion׼������*/
		memset(loc,0,sizeof(int)*Edge);
		for(int k = 1; k < RouteS[chglp][0]; k++ )
		{
			int v1 = RouteS[chglp][k];
			int v2 = RouteS[chglp][k+1];
			loc[ChartMat[v1][v2]] = 1;
		}
		/*estimatetion׼������*/
		for ( int j = 0 ; j <= Color ; j++ )
		{
			if ( j == mincolor )
				continue ;
			value = EstimationOfChgColor(chglp,j);
			if ( value < minvalue )
			{
				minvalue = value ;
				chgcolor = j ;
			}
		}
		if ( minvalue == INT_MAX )
		{
			cout<<"change error!"<<endl;
			exit(0);
		}
		num = ++LIDC[chgcolor][0] ;
		LIDC[chgcolor][num] = chglp ;
		ColorS[chglp] = chgcolor ;
	}
	memset(LIDC[mincolor],-1,sizeof(int)*LP);
	for ( int i = 1 ; i <= LIDC[Color][0] ; i++ )//����Color����ɫ�Ƶ���mincolor��,�м䲿��ֵ���ܻ���-1
	{
		int ps = LIDC[Color][i];
		LIDC[mincolor][i] = ps ;
		ColorS[ps] = mincolor ;
	}
	LIDC[mincolor][0] = LIDC[Color][0] ;
	Color-- ;//�������һ�����?
	InitIncChart() ;
	cout<<"��ǰ��ɫ�� = "<<Color+1<<"�� ��ͻ��="<<AllConflict/2<<" ����ʱ�� = "<<(end-start)/1000<<endl;
}
//void RWA::SubColor()
//{
//	//cout<<"SubColor..."<<endl;
//	//�������? 
//	int min = INT_MAX , mincolor ;
//	float end = clock() ;
//	for ( int i = 0 ; i <= Color ; i++ )
//	{
//		if ( min > LIDC[i][0] )
//		{
//			min = LIDC[i][0] ;
//			mincolor = i ;
//		}
//	}
//	int minnum = LIDC[mincolor][0] ;
//	//LIDC[mincolor][0] = 0 ;
//	for ( int i = 1 ; i <= minnum ; i++ )//ɾ����mincolor����ɫ��lightpath������䵽�������?
//	{
//		int cor =  rand()%Color ;
//		int chglp = LIDC[mincolor][i] ;
//		if ( cor == mincolor )//��ΪҪ�����һ�����?����Ҫɾ������ɫ���������·�����ɫʱ�����䵽mincolor�Ĺ�·���䵽Color��
//		{
//			int num = LIDC[Color][0] ;
//			LIDC[Color][num+1] = chglp ;
//			LIDC[Color][0]++ ;
//			ColorS[chglp] = Color ;
//		}
//		else 
//		{
//			int num = LIDC[cor][0] ;
//			LIDC[cor][num+1] = chglp ;
//			LIDC[cor][0]++ ;
//			ColorS[chglp] = cor ;
//		}
//	}
//	memset(LIDC[mincolor],-1,sizeof(int)*LP);
//	for ( int i = 1 ; i <= LIDC[Color][0] ; i++ )//����Color����ɫ�Ƶ���mincolor��,�м䲿��ֵ���ܻ���-1
//	{
//		int ps = LIDC[Color][i];
//		LIDC[mincolor][i] = ps ;
//		ColorS[ps] = mincolor ;
//	}
//	LIDC[mincolor][0] = LIDC[Color][0] ;
//	Color-- ;//�������һ�����?
//	InitIncChart() ;
//	cout<<"��ǰ��ɫ�� = "<<Color+1<<"�� ��ͻ��="<<AllConflict<<" ����ʱ�� = "<<(end-start)/1000<<endl;
//}
int RWA::EstimationOfChgColor( int lp , int color )
{
	int v1, v2, nc, precolor = ColorS[lp];
	int Incvalue = 0;
	nc = LIDC[color][0];
	for(int i = 1; i <= nc; ++i)
	{
		int currlp = LIDC[color][i];
		for(int j = 1; j < RouteS[currlp][0]; ++j)
		{
			v1 = RouteS[currlp][j];
			v2 = RouteS[currlp][j+1];
			
			if(loc[ChartMat[v1][v2]] == 1)
				Incvalue = Incvalue + 2;
		}
	}
	return (Incvalue - 2 * Conflict[lp]);//δ����ͻ��-��ǰ��ͻ��
}
void RWA::UpdataIncChart(int ChgLp , int ChgColor)
{
	//����������
	//cout<<"UpdataIncChart..."<<endl;
	memset(IncChart[ChgLp], 0, sizeof(int) * Edge);
	memset(IncChartt[ChgLp], 0, sizeof(int) * Edge);
	int v1 , v2 , nc ; 
	int precolor = ColorS[ChgLp] ;
	nc = LIDC[precolor][0] ; 
	for ( int i = 1 ; i <= nc ; i++ )//������
	{
		int currlp = LIDC[precolor][i] ;
		if ( currlp == ChgLp  )
		{
			continue ;
		}
		for ( int j = 1 ; j < RouteS[ChgLp][0] ; j++ )
		{
			v1 = RouteS[ChgLp][j] ;
			v2 = RouteS[ChgLp][j+1] ;
			int position = ChartMat[v1][v2];
			IncChart[currlp][position]-- ;
			IncChartt[currlp][position]-=weight[currlp] ;
			IncChartCopy[currlp][position] = IncChart[currlp][position] ;
			if ( IncChart[currlp][position] < 0 )
			{
				cout<<" UpdataIncChart ������ error ! "<<currlp<<" "<<ColorS[currlp]<<endl;
				exit(0);
			}
		}
		Conflict[currlp] = 0 ;
		for ( int j = 1 ; j < RouteS[currlp][0] ; j++ )
		{
			v1 = RouteS[currlp][j] ; 
			v2 = RouteS[currlp][j+1] ;
			int position = ChartMat[v1][v2];
			Conflict[currlp] += IncChart[currlp][position];
			weight[currlp] += IncChartt[currlp][position];
		}
	}
	nc = LIDC[ChgColor][0] ; 
	for ( int i = 1 ; i <= nc ; i++ )
	{
		int currlp = LIDC[ChgColor][i] ;
		for ( int j = 1 ; j < RouteS[ChgLp][0] ; j++ )//�Ӳ���
		{
			v1 = RouteS[ChgLp][j] ; 
			v2 = RouteS[ChgLp][j+1] ;
			int position = ChartMat[v1][v2];
			IncChart[currlp][position]++ ;
			IncChartt[currlp][position]+=weight[currlp] ;
			IncChartCopy[currlp][position] = IncChart[currlp][position] ;
		}
		Conflict[currlp] = 0 ;//���¼���Conflict
		for ( int j = 1 ; j < RouteS[currlp][0] ; j++ )
		{
			v1 = RouteS[currlp][j] ; 
			v2 = RouteS[currlp][j+1] ;
			int position = ChartMat[v1][v2];
			Conflict[currlp] += IncChart[currlp][position];
			weight[currlp] += IncChartt[currlp][position];
			IncChart[ChgLp][position]++ ;
			IncChartt[ChgLp][position]+=weight[ChgLp];
			IncChartCopy[ChgLp][position] = IncChart[ChgLp][position] ;
		}
	}
	Conflict[ChgLp] = 0 ;//���¼���ChgLp��Conflict
	for ( int j = 1 ; j < RouteS[ChgLp][0] ; j++ )
	{
		v1 = RouteS[ChgLp][j] ; 
		v2 = RouteS[ChgLp][j+1] ;
		int position = ChartMat[v1][v2];
		Conflict[ChgLp] += IncChart[ChgLp][position];
		weight[ChgLp] += IncChartt[ChgLp][position];
	}
	AllConflict = 0 ;
	for ( int i = 0 ; i < LP ; i++ )
	{
		if (  Conflict[i] < 0 )
		{
			cout<<"0 error "<<i<<endl;
			exit(0) ;
		}
		AllConflict += Conflict[i];
	}
	ColorS[ChgLp] = ChgColor ; 
	//�޸�LIDC��
	nc = LIDC[precolor][0] ; 
	for ( int i = 1 ; i <= nc ; i++ )
	{
		if ( LIDC[precolor][i] == ChgLp )//��ChgLpλ�������һ��ֵ����?
		{
			LIDC[precolor][i] = LIDC[precolor][nc] ;
			LIDC[precolor][nc] = -1 ;
			LIDC[precolor][0]-- ;
			break;
		}
	}
	//ChgColor��ɫ����һ��ֵ
	nc =  LIDC[ChgColor][0] ;
	LIDC[ChgColor][nc+1] = ChgLp ;
	LIDC[ChgColor][0]++ ; 
}

int *RWA::Pseudo_DFS( int lp )
{
	//�ҳ������г�ͻlightpath�����Ž�
	int  top = 1 ,v1 ,v2 ,CF , edge;

	for ( int i = 0 ; i < N ; i++ )
		memset(visit_edge[i],0,sizeof(int)*N) ;
	memset(visit_vec,0,sizeof(int)*N) ;
	memset(prt,-1,sizeof(int)*N) ;
	memset(d,0,sizeof(int)*N) ;
	memset(tempS,-1,sizeof(int)*N);
	int *Best = (int*)malloc(sizeof(int)*hop);
	memset(Best,-1,sizeof(int)*hop) ;

	v1 = RouteS[lp][1];
	v2 = RouteS[lp][RouteS[lp][0]];
	CF = Conflict[lp];

	tempS[top] = v1 ;//visit[v1] = 1 ; 
	visit_vec[v1] = 1 ;

	while ( true )
	{
		int cv = tempS[top] ;
		int i ; 
		for ( i = 0 ; i < N ; i++ )
		{
			if ( top + 1 == hop )
				break;
			if ( Mat[cv][i] == 0 )
				continue ;
			edge = ChartMat[cv][i] ;
			int Addcf = IncChart[lp][edge] ;
			if ( visit_edge[cv][i] != 1 && d[cv]+Addcf < CF && visit_vec[i] == 0 )//&& visit[i] != 1
			{
				prt[i] = cv ; visit_edge[cv][i] = 1 ; d[i] = d[cv]+Addcf ;
				tempS[++top] = i ;visit_vec[i] = 1 ; 
				break;
			}
		}
		if ( tempS[top] == v2 && d[i] < CF )
		{
			tempS[0] = top ;//�ⳤ��
			memset(Best,-1,sizeof(int)*hop) ;
			for ( int j = 0 ; j <= tempS[0] ; j++ )
			{
				Best[j] = tempS[j] ;
			}
			CF = d[i] ;
			//return tempS ;//����һ���ҵ��Ľ�
		}
		if ( cv == tempS[top] && cv == v1 )
		{
			tempS[0] = -1 ;
			break;
			//return NULL;//tempS ;//û���ҵ���
		}
		if ( cv != tempS[top] && i != v2 )
			continue ;

		for ( int k = 0 ; k < N ; k++ )
		{
			if ( prt[k] == tempS[top] )
			{
				visit_edge[prt[k]][k] = 0 ;
				//visit_vec[k] = 0 ; 
				prt[k] = -1 ;
			}
		}
		visit_vec[tempS[top]] = 0 ;
		tempS[top] = -1 ; 
		top-- ;
	}
	for ( int j = 0 ; j <= Best[0] ; j++ )
	{
		tempS[j] = Best[j] ;
	}
	free(Best);
	if ( tempS[0] != -1 )
		return tempS ;
	else 
		return NULL ;
}

int *RWA::Pseudo_DFS( int lp , int cf )
{
	//cout<<"Pseudo_DFS.."<<endl;
	int  top = 1 ,v1 ,v2 ,CF , edge ,limitConf;

	for ( int i = 0 ; i < N ; i++ )
		memset(visit_edge[i],0,sizeof(int)*N) ;
	memset(visit_vec,0,sizeof(int)*N) ;
	memset(prt,-1,sizeof(int)*N) ;
	memset(d,0,sizeof(int)*N) ;
	memset(tempS,-1,sizeof(int)*N);
	/*��cf==0ʱ�����Ŷ�Ѱ·������ɫ��*/
	if( cf == 0 )
	{
		memset(loc,0,sizeof(int)*Edge) ;
		int color = ColorS[lp] ;
		for ( int i = 1 ; i <= LIDC[color][0] ; i++ )
		{
			int temp = LIDC[color][i] ;
			for ( int j = 1 ; j < RouteS[temp][0] ; j++ )
			{
				int v1 = RouteS[temp][j];
				int v2 = RouteS[temp][j+1];
				int pos = ChartMat[v1][v2];
				loc[pos]++ ;
			}
		}
		limitConf = 0 ;//��֤ÿһ���������г�ͻ  
	}
	else 
	{
		limitConf = cf ;
	}
	v1 = RouteS[lp][1];
	v2 = RouteS[lp][RouteS[lp][0]];
	//CF = cf ;//Conflict[lp];
	
	tempS[top] = v1 ;//visit[v1] = 1 ; 
	visit_vec[v1] = 1 ;

	while ( true )
	{
		int cv = tempS[top] ;
		int i ; 
		for ( i = 0 ; i < N ; i++ )
		{
			if ( top + 1 == hop )
				break;
			if ( Mat[cv][i] == 0 )
				continue ;
			edge = ChartMat[cv][i] ;
			if ( cf == 0 )
			{
				int Addcf = loc[edge] ;
				CF = Addcf ;
			}
			else
			{
				int Addcf = IncChart[lp][edge] ;
				CF = d[cv]+Addcf ;
			}
			if ( visit_edge[cv][i] != 1 && CF <= limitConf && visit_vec[i] == 0 )//&& visit[i] != 1
			{
				prt[i] = cv ; visit_edge[cv][i] = 1 ;
				if ( cf != 0 )
					d[i] = CF ;
				tempS[++top] = i ;visit_vec[i] = 1 ; 
				break;
			}
		}
		if ( tempS[top] == v2 && d[i] < limitConf && cf != 0 )//�޸�
		{
			tempS[0] = top ;//�ⳤ��
			return tempS ;
		}
		if ( tempS[top] == v2 && cf == 0 )
		{
			tempS[0] = top ;//�ⳤ��
			return tempS ;
		}
		if ( cv == tempS[top] && cv == v1 )
		{
			tempS[0] = -1 ;
			return NULL ;
			//return NULL;//tempS ;//û���ҵ���
		}
		if ( cv != tempS[top] && i != v2 )
			continue ;

		for ( int k = 0 ; k < N ; k++ )
		{
			if ( prt[k] == tempS[top] )
			{
				visit_edge[prt[k]][k] = 0 ;
				//visit_vec[k] = 0 ; 
				prt[k] = -1 ;
			}
		}
		visit_vec[tempS[top]] = 0 ;
		tempS[top] = -1 ; 
		top-- ;
	}
}

void RWA::RecordFile()
{
	int value = Check();
	if ( value != 0 )
	{
		cout<<"Route result not equal zero !! ��RecordFile��"<<endl;
		exit(0);
	}
	string recFilename("New_Result\\");
	//string recFilename("E:\\612\\personal\\yanshengfeng\\RWA\Result\\");
	recFilename = recFilename + instancesname + "_result.txt"; 
	ofstream fout(recFilename.c_str());//,ios::app
	 if ( fout.fail() )
     {
           cout << "### Erreur open, result.txt "<< endl;
           exit(0);
     }
     if ( fout.eof() )
     {
           cout << "### Error open, result.txt "<< endl;
           exit(0);
     }
	 float end = clock();
	 fout<<"AllConflict = "<<AllConflict<<" Color = "<<Color+1<<" time = "<<(end-start)/1000<<endl;
	// fout<<"solution:(Lightpath -- Route -- Color)"<<endl;
	 fout<<"Lightpath -- Color -- RouteS "<<endl;
	 for ( int i = 0 ; i < LP ; i++ )
	 {
		 fout<<i<<" "<<ColorS[i]<<" ";
		 for ( int j = 0 ; j <= RouteS[i][0] ; j++ )
		 {
			 fout<<RouteS[i][j]<<" ";
		 }
		 fout<<endl;
	 }
	 fout.close() ; 
}

int *RWA::Pseudo_BFS( int lp )//int v1 , int v2 , int CF
{
	//int *S = (int*)malloc(sizeof(int)*10);
	memset(tempS,-1,sizeof(int)*10);
	int front = 0 , index = 0 , best = -1 ;
	int v1 , v2 , CF ; 

	v1 = RouteS[lp][1];//��·lp�ϵĵ�һ���ڵ�
	v2 = RouteS[lp][RouteS[lp][0]];//��·lp�ϵ����һ���ڵ�?
	CF = Conflict[lp];

	vector<int> point ;
	vector<int> parent ;
	vector<int> st ;
	vector<int> dist;
	point.push_back(v1);
	parent.push_back(-1);
	dist.push_back(0);

	bool flag = true ;
	int subhop , count = 1 ; 
	while(true)
	{
		int cv = point[front] ;
		if ( cv == v2 )//�ж��Ƿ��ߵ����һ���ڵ���?
		{
			front++ ;
			if ( front >= point.size() )
				break;
			continue ;
		}
		for ( int i = 0 ; i < N ; i++ )
		{
			//�ж�i��֮ǰ��û�г��֣������γɻ�
			if ( Mat[cv][i] == 0 || i == cv )
				continue ;
			flag = true ;
			index = front;
			subhop = 1 ;
			while(true)
			{
				int p = parent[index] ;
				if ( p == -1 )
					break;
				if ( point[p] == i )
				{
					flag = false ;
					break;
				}
				index = p ;
				subhop++ ;//��ĳ���?
			}

			int edge = ChartMat[cv][i] ;
			int Addcf = IncChart[cv][edge] ;
			if ( dist[front]+Addcf < CF && flag && subhop < hop )
			{
				point.push_back(i) ;
				parent.push_back(front);
				dist.push_back(dist[front]+Addcf);
				if ( point.back() == v2 )
				{
					CF = dist.back();
					best = front ;
					//break;
				}
				count = 1 ;
			}
			else if ( dist[front]+Addcf == CF && flag && subhop < hop && rand()%(++count)==0 )
			{
				point.push_back(i) ;
				parent.push_back(front);
				dist.push_back(dist[front]+Addcf);
				if ( point.back() == v2 )
				{
					best = front ;
				}
			}
		}
		front++ ;
		if ( front >= point.size() )
		{
			//return NULL ;
			break;
		}
	}
	//cout<<"out"<<endl;
	if( best != -1 )//point.back() == v2
	{
		index = best ;//front ;
		vector<int> ts ;
		ts.push_back(v2);
		ts.push_back(point[index]);
		while ( true )
		{
			int p = parent[index];
			if ( p == -1 )
				break;
			ts.push_back(point[p]);
			index = p ;
		}
		tempS[0] = ts.size();
		int k = 1 ;
		while ( !ts.empty() )
		{
			tempS[k++] = ts.back() ;
			ts.pop_back();
		}
		point.clear();
		parent.clear();
		dist.clear();
		return tempS ;
	}
	else 
	{
		point.clear();
		parent.clear();
		dist.clear();
		return NULL ;
	}

}

void RWA::InitNewGraph()//��ȡ��ɫ��ColorS��NewGraph���г�ʼ��
{
	NewGraph = (int**)malloc(sizeof(int*) * LP);
	for (int i = 0; i < LP; i++)
	{
		NewGraph[i] = (int*)malloc(sizeof(int) * Edge);
		memset(NewGraph[i], -1, sizeof(int) * Edge);
		for (int j = 1; j < RouteS[i][0]; ++j)
		{
			int v1 = RouteS[i][j];
			int v2 = RouteS[i][j + 1];
			int edge = ChartMat[v1][v2];
			NewGraph[i][edge] = ColorS[i];
		}
	}
}
void RWA::UpdateLPVariation(int lp)//��¼��ǰ��··������������·���غϹ�ϵ
{
	int v1, v2, precolor = ColorS[lp];
	int Incvalue = 0;
	for (int i = 0; i < Edge; i++)
	{
		memset(LPVariation[i], 0, sizeof(int*) * (Color));
	}
	memset(ReplaceLoc, ColorS[lp], sizeof(int) * Edge);
	memset(loc, 0, sizeof(int) * Edge);
	for (int i = 1; i <= LP; ++i)//ѭ�����й�·
	{
		for (int j = 1; j < RouteS[i][0]; ++j)
		{
			v1 = RouteS[i][j];
			v2 = RouteS[i][j + 1];
			int edge = ChartMat[v1][v2];
			if (NewGraph[lp][edge] != -1)
			{
				++LPVariation[edge][NewGraph[lp][edge]];
			}
		}
	}
}

int RWA::EstimationOfCandC(int lp, int weight)//ͬʱ������ǰ��·��ͨ���Լ���ͻ��
{
	int v1, v2, precolor = ColorS[lp];
	int Incvalue = 0;
	int prev = ReplaceLoc[ChartMat[RouteS[lp][1]][RouteS[lp][2]]];
	int unconnection = 0, newconflict = 0, originconflict = 0;

	//Incvalue = 2 * Conflict[lp];
	//LPVariation[ChartMat[v1][v2]][0]
	for (int i = 1; i < RouteS[lp][0]; ++i)
	{
		v1 = RouteS[lp][i];
		v2 = RouteS[lp][i + 1];
		
		if (ReplaceLoc[ChartMat[v1][v2]] != prev)
		{
			unconnection += weight;//����ͨ������
			newconflict += LPVariation[ChartMat[v1][v2]][ReplaceLoc[ChartMat[v1][v2]]];//�³�ͻ����
		}
		else
			originconflict += IncChart[i][ChartMat[v1][v2]];

		prev = ReplaceLoc[ChartMat[v1][v2]];
	}

	Incvalue += 2 * (originconflict + unconnection + newconflict);

	return (Incvalue - MixWeight[lp]);
}

int RWA::ReplaceColor(int lp, int* route)//���ڲ��ҹ�·���ܸ���������ɫ
{
	int curnum = 0, maxnum = 0, mostcommoncolor = 0;
	int* colors = (int*)malloc(sizeof(int) * (Color));//ͳ��ÿ����ɫ�ĸ���
	memset(colors, 0, sizeof(int) * Color);
	if (Color == 0)
		cerr << "ColorΪ0" << endl;
	for (int k = 0; k < RouteS[lp][0]; k++)//ͳ��������û������?
	{
		int v1 = RouteS[lp][k];
		int v2 = RouteS[lp][k + 1];
		int edge = ChartMat[v1][v2];
		if (route[edge] != -1)
			++colors[route[edge]];
		else
			cout << "·�ɶ�ȡʧ��================================================" << endl;
	}
	for (int i = 0; i < Color; ++i)
	{
		if (colors[i] > maxnum)
		{
			maxnum = colors[i];
			mostcommoncolor = i;//�õ���·�ϳ�����Ƶ������ɫ
		}
	}
	return mostcommoncolor;
}

bool RWA::ColorConnection()//ͬʱ�ı���ɫ��·��
{
	int iteration = 0, jug;
	int *bestroute = (int*)malloc(sizeof(int) * (Edge));
	memset(bestroute, -1, sizeof(int) * Edge);
	bool flag = false, iflag = false;
	if (AllConflict == 0)//Ŀ�꺯������0�����һ�����?
	{
		cout << "AllConflict = 0 " << endl;
		iflag = true;
		RecordFile();
		SubColor();
		memset(Tabu, -1, sizeof(int) * LP);
		iteration = 0;
	}

	int ChgLp = 0, ChgColor = ColorS[0], ChgEdge = 0;//Ҫ�ı��LightPath����ɫ,��ʼֵΪ0������ɫ��0
	int MinValue = INT_MAX, CurrentValue;//AllConflict
	int EqProb = 1;

	
	//ÿ�λ���һ��lightpath�任��������ɫ/LIDCͬʱ��
	for (int i = 0; i < LP; i++)
	{
		if (Conflict[i] == 0)
			continue;
		/*estimatetion׼������*/
		UpdateLPVariation(i);

		for (int j = 0; j < RouteS[i][0]; j++)
		{
			int v1 = RouteS[i][j];
			int v2 = RouteS[i][j + 1];//������ǰ��·��������
			int edge = ChartMat[v1][v2];
			int precolor = ColorS[i];
			if (ColorS[i] == j || Tabu[i] != -1)
			{
				Tabu[i] = -1;//����ǰ��·���?
				continue;
			}
			for (int c = 0; c < Color; c++)
			{
				precolor = ReplaceLoc[edge];
				ReplaceLoc[edge] = c;
				CurrentValue = EstimationOfCandC(i, 1);//���۸Ķ���ĳ�ͻ�Ժ����?��
				if (MinValue > CurrentValue) //�����˱ȵ�ǰ��Ҫ��Ľ�?
				{
					MinValue = CurrentValue;
					flag = true;
					EqProb = 1;
				}
				else if (MinValue == CurrentValue && rand() % (++EqProb) == 0)//�ȸ��ʽ���ͬ��ֵ�Ľ�
				{
					flag = true;
				}
				else
				{
					ReplaceLoc[edge] = precolor;
				}
			}
		}
		if (flag)
		{
			ChgLp = i;
			for (int j = 0; j < RouteS[i][0]; j++)
			{
				int v1 = RouteS[i][j];
				int v2 = RouteS[i][j + 1];//������ǰ��·��������
				int edge = ChartMat[v1][v2];
				NewGraph[i][edge] = ReplaceLoc[edge];
			}
			UpdateLPVariation(ChgLp);
		}
	}

	//�ظ�����Ĳ���?������ͨ��Ȩ�ظ�Ϊ5
	if (AllConflict == 0)//Ŀ�꺯������0�����һ�����?
	{
		cout << "AllConflict = 0 " << endl;
		iflag = true;
		RecordFile();
		SubColor();
		memset(Tabu, -1, sizeof(int) * LP);
		iteration = 0;
	}

	ChgLp = 0, ChgColor = ColorS[0], ChgEdge = 0;
	MinValue = INT_MAX, CurrentValue;//AllConflict
	EqProb = 1;
	//ÿ�λ���һ��lightpath�任��������ɫ/LIDCͬʱ��
	for (int i = 0; i < LP; i++)
	{
		if (Conflict[i] == 0)
			continue;
		/*estimatetion׼������*/
		UpdateLPVariation(i);

		for (int j = 0; j < RouteS[i][0]; j++)
		{
			int v1 = RouteS[i][j];
			int v2 = RouteS[i][j + 1];//������ǰ��·��������
			int edge = ChartMat[v1][v2];
			int precolor = ColorS[i];
			//if (ColorS[i] == j || Tabu[i] != -1)
			//{
			//	Tabu[i] = -1;//����ǰ��·���?
			//	continue;
			//}
			for (int c = 0; c < Color; c++)
			{
				precolor = ReplaceLoc[edge];
				ReplaceLoc[edge] = c;
				CurrentValue = EstimationOfCandC(i, 5);//���۸Ķ���ĳ�ͻ�Ժ����?��
				if (MinValue > CurrentValue) //�����˱ȵ�ǰ��Ҫ��Ľ�?
				{
					MinValue = CurrentValue;
					flag = true;
					EqProb = 1;
				}
				else if (MinValue == CurrentValue && rand() % (++EqProb) == 0)//�ȸ��ʽ���ͬ��ֵ�Ľ�
				{
					flag = true;
				}
				else
				{
					ReplaceLoc[edge] = precolor;
				}
			}
		}
		if (flag)
		{
			ChgLp = i;
			for (int j = 0; j < RouteS[i][0]; j++)
			{
				int v1 = RouteS[i][j];
				int v2 = RouteS[i][j + 1];//������ǰ��·��������
				int edge = ChartMat[v1][v2];
				NewGraph[i][edge] = ReplaceLoc[edge];
			}
			UpdateLPVariation(ChgLp);
		}
	}

	if (flag)
	{
		jug = AllConflict;
		ChgColor = ReplaceColor(ChgLp, bestroute);
		Tabu[ChgLp] = ColorS[ChgLp];
		UpdataIncChart(ChgLp, ChgColor);//����Ҫ��
	}
	return iflag;
}
