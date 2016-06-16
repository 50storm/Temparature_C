#include <stdio.h>
#include <string.h>
#define DEBUG 0
#define println()(printf("\n"))
/*  prototype functions */

struct temparature_type{
  int month;
  double day_avg;
  double day_max;
  double day_min;
  double month_max;
  double month_min;
};

int set_tempra_data(struct temparature_type * );
int main(int argc, const char * argv[]) {
	/*初期処理*/
	//月別のファイル読み込み
  FILE* fp;
  double TmpData[12][6];
  int i,j;
  for(i=0; i<12; i++){
    for(j=0; j<6; j++){
      TmpData[i][j]=0.0;
    }
  }
  fp = fopen("temprature_2015.dat", "r");
  //ファイルが見つからなければ、エラー終了
  if(fp==NULL){
    printf("File does not exist.");
    return -1;
  }

  struct temparature_type tempra_data_2015[1000];
  int data[1000];
  char buf[1000];
  int cnt = 0;
  int k=0;

  while (fgets(buf, 256, fp) != NULL) {
        int ret = sscanf(buf, "%d"  "%lf"  "%lf"
                              "%lf"  "%lf"  "%lf", 
                        &tempra_data_2015[k].month, &tempra_data_2015[k].day_avg, &tempra_data_2015[k].day_max, 
                        &tempra_data_2015[k].day_min, &tempra_data_2015[k].month_max, &tempra_data_2015[k].month_min
                        );//ok
        printf("%d\n",ret);//6
        
        k++;
  }
  for(k=0; k<12 ; k++){
    printf("debugging\t");
    printf("month=%d \t day_avg=%f \t day_max=%f \t day_min=%f \t month_max=%f \t month_min=%f ", 
          tempra_data_2015[k].month , tempra_data_2015[k].day_avg , tempra_data_2015[k].day_max , tempra_data_2015[k].day_min , tempra_data_2015[k].month_max, tempra_data_2015[k].month_min);
    println();
  }
  
  fclose(fp);

/*

hiroshi-mac:9 hiroshi$ ./a.out 
6
6
6
6
6
6
6
6
6
6
6
6
debugging month=1    day_avg=4.500000    day_max=9.900000    day_min=-1.200000   month_max=17.100000   month_min=-6.200000 
debugging month=2    day_avg=4.400000    day_max=9.700000    day_min=-0.900000   month_max=17.700000   month_min=-7.200000 
debugging month=3    day_avg=8.900000    day_max=14.800000   day_min=2.900000    month_max=23.800000   month_min=-4.700000 
debugging month=4    day_avg=13.300000   day_max=18.700000   day_min=7.800000    month_max=28.000000   month_min=0.900000 
debugging month=5    day_avg=19.200000   day_max=25.000000   day_min=13.500000   month_max=28.600000   month_min=6.000000 
debugging month=6    day_avg=20.800000   day_max=25.300000   day_min=16.800000   month_max=29.600000   month_min=11.500000 
debugging month=7    day_avg=25.300000   day_max=29.800000   day_min=21.900000   month_max=34.400000   month_min=18.100000 
debugging month=8    day_avg=25.600000   day_max=29.900000   day_min=22.700000   month_max=36.800000   month_min=18.700000 
debugging month=9    day_avg=22.000000   day_max=26.000000   day_min=18.800000   month_max=30.900000   month_min=12.000000 
debugging month=10   day_avg=17.400000   day_max=22.100000   day_min=12.600000   month_max=27.300000   month_min=4.400000 
debugging month=11   day_avg=13.400000   day_max=17.800000   day_min=8.900000    month_max=24.000000   month_min=-1.200000 
debugging month=12   day_avg=8.000000    day_max=13.100000   day_min=2.500000    month_max=24.000000   month_min=-4.800000



*/



/*
  配列に格納OK

  while (fgets(buf, 256, fp) != NULL) {
        int ret = sscanf(buf, "%d", &data[k]);// compile success
        
        k++;
  }
  for(k=0; k<12 ; k++){
    printf("%d", data[k]);
    println();
  }


*/
	return 0;
}