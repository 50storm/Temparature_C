/*

今回でC言語の学習は終了し、次回から検索や並べ替えのアルゴリズムの実装にとりか かります。そこで、今回はこれまでに学習したことの総まとめとして、
条件分岐、繰り返し、 配列、関数、など学んだことを駆使して、過去数十年間の月別平均気温のデータをファイル から配列に読み込み、下記の1~6に沿って各自でそのデータを利用したオリジナルのプ ログラムを作成してください。
1 少なくとも過去10年分以上のデータを読み込む。
 第7回配布のサンプルでは東京の 2000 年~2013 年の 14 年間のデータを使用しまし たので、そのまま利用しても構いませんが、
 次ページの「使用する平均気温データに ついて」を参考にして自分の住んでいる地域の過去 100 年分あるいは観測開始以来の 
 全ての年などを読み込んでみるのも面白いでしょう。
2 キーボードから指定した○年△月のデータを表示する。 これもサンプルファイルを実行するだけで出来ますが
、1 度だけでなく何度もこの機 能を繰り返せるようにするとか、2000 年より以前のデータも読み込んでおき配列の 要素番号と西暦年の対応を考えて取り組むなど、いろいろ工夫も出来そうです。
3 キーボードから指定した月について、読み込んだ全期間あるいは 
10 年間の平均を計 算し表示すること。
過去 20 年間、30 年間など平均する期間を指定するといった凝ったことも出来ます。
4 エラー処理をすること。
入力された月の値が(-2)月や 13 月など不適切な値の場合には、無視してもう一度入力 を促す、あるいは、エラーメッセージを表示する、などエラー処理をしてください。
5 関数を定義して使ってみること。 例えば、月の入力を促し入力値が適切か調べエラー処理をするという一連の処理を関 数にしてみたり、凝ったタイトル表示部分を関数にしてまとめてみるなど。
6 その他にもいろいろな工夫をぜひ試してください 繰り返し比較して「過去○年間で一番寒かった□月」を調べてみるなど、アイデア次 第でいろいろと工夫してみてください。
まずは、第7回で配布した 7-4-temperature.c と temp_tokyo.txt というファイルを元にし て始めてみましょう。12はサンプルを動かすだけで出来てしまうはずです。出来なかった としても出来たところまで期限には提出してください。

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1
#define println()(printf("\n"))
#define INDEX 12
#define INDEX_ALL 12*14

enum enumMENU {MONTHLY_DATA = 1 , FIND_MAX_DATA = 2, COMPUTE_AVG_DATA = 3,  EXIT = 9, ERR = -1  } MENU ;
enum enumSUBMENU{AVG_DATA=1, MAX_DATA=2, MIN_DATA=3, ALL_DATA=4, EXIT_SUB=9} SUBMENU ;
enum enumSUBMENU_FIND{FIND_MENU_AGV_DAY=1, FIND_MENU_AGV_MAX=2, FIND_MENU_AGV_MIN=3, FIND_MENU_MAX_DATA=4, FIND_MENU_MIN_DATA=5, FIND_MENU_EXIT_SUB=9} SUB_FIND_MENU ;
enum enumSUBMENU_CMP_AVG{CMP_AVG_MENU_AGV_DAY=1, CMP_AVG_MENU_AGV_MAX=2, CMP_AVG_MENU_AGV_MIN=3, CMP_AVG_MENU_MAX_DATA=4, CMP_AVG_MENU_MIN_DATA=5, CMP_AVG_EXIT_SUB=9} SUB_CMP_AVG_MENU ;

struct temparature_type{
  int month;
  double day_avg;
  double day_max;
  double day_min;
  double month_max;
  double month_min;
};

struct  user_input_type{
    int year;
    int month;
	int period;
	int from_year;
	int to_year;

};

/*prototype*/
int show_menu(void);
int show_monthly_menu(void);
int show_find_menu(void);
int set_tempara_data(struct temparature_type *, char [] );
int set_tempara_data_all(struct temparature_type * , char [] );
int set_input_date( struct user_input_type * );
int set_input_date_period( struct user_input_type * );
int find_max_data(int SUB_FIND_MENU_TYPE, struct user_input_type * , struct temparature_type * );
int compute_avg_data(int SUB_FIND_MENU_TYPE, struct user_input_type * , struct temparature_type * );

void showErrMsg(const char *msg , double d_val, int i_val){
  if( i_val == 0 && d_val !=0.0 )
  {
    printf("Wrong input:%s:%f \n\n",msg, d_val);
  }
  else if( i_val != 0 && d_val ==0.0 )
  {
    printf("Wrong input:%s:%d \n\n",msg, i_val);
  }
}

int show_monthly_day_avg(int flg_type, struct user_input_type *user_input , struct temparature_type *temara_data )
{
	
	switch(SUBMENU){
		case AVG_DATA:
			printf("-------[%d][%d][Average Temparature of Day]--------------\n",  user_input->year , user_input->month );
			printf("Average(AVG)[%.1lf] | Avarage(MAX)[%.1lf]  | Avarage(MIN)[%.1lf]   \n" ,  temara_data[user_input->month-1].day_avg,temara_data[user_input->month-1].day_max, temara_data[user_input->month-1].day_min );
			printf("---------------------------------------------------------\n");
		break;
		
		case MAX_DATA:
			printf("-------[%d][%d][Max Temparature in the Month]--------------\n",  user_input->year , user_input->month );
			printf("MAX[%.1lf] \n" ,  temara_data[user_input->month-1].month_max );
			printf("---------------------------------------------------------\n");
		break;

		case MIN_DATA:
			printf("-------[%d][%d][Min Temparature in the Month]--------------\n",  user_input->year , user_input->month );
			printf("MAX[%.1lf] \n" ,  temara_data[user_input->month-1].month_min );
			printf("---------------------------------------------------------\n");
		break;
		
		case ALL_DATA:
			printf("-------[%d][%d][Average Temparature of Day]--------------\n",  user_input->year , user_input->month );
			printf("Average(AVG)[%.1lf] | Avarage(MAX)[%.1lf]  | Avarage(MIN)[%.1lf]   \n" ,  temara_data[user_input->month-1].day_avg,temara_data[user_input->month-1].day_max, temara_data[user_input->month-1].day_min );
			printf("---------------------------------------------------------\n");
			printf("-------[%d][%d][Max Temparature in the Month]--------------\n",  user_input->year , user_input->month );
			printf("MAX[%.1lf] \n" ,  temara_data[user_input->month-1].month_max );
			printf("---------------------------------------------------------\n");
			printf("-------[%d][%d][Min Temparature in the Month]--------------\n",  user_input->year , user_input->month );
			printf("MAX[%.1lf] \n" ,  temara_data[user_input->month-1].month_min );
			printf("---------------------------------------------------------\n");

		break;
		
		case EXIT_SUB:
		break;
	}
      
#if DEBUG ==1
      int i;
      for(i=0; i < 12 ;i++){
        printf("%lf\n" ,  temara_data[i].day_avg );
      }
#endif 
	return 0;
}
//TODO;使わないかも
int find_max_data_12(int flg_type, struct temparature_type *temara_data, double *ret_data )
{
	int i;
	double tmp;
	
	switch(SUB_FIND_MENU){
		case FIND_MENU_AGV_DAY:
		tmp = temara_data[0].day_avg;
		for(i=1; i<12; i++){
			if(tmp < temara_data[i].day_avg )
			{
				tmp=temara_data[i].day_avg;
			}
			
		}

		break;
		
		case FIND_MENU_AGV_MAX:
		SUB_FIND_MENU=FIND_MENU_AGV_MAX;
		break;
		
		case FIND_MENU_AGV_MIN:
		SUB_FIND_MENU=FIND_MENU_AGV_MIN;
		break;
		
		case FIND_MENU_MAX_DATA:
		SUB_FIND_MENU=FIND_MENU_MAX_DATA;
		break;
		
		case FIND_MENU_MIN_DATA:
		SUB_FIND_MENU=FIND_MENU_MIN_DATA;
		break;
		
		case FIND_MENU_EXIT_SUB:
		SUB_FIND_MENU=FIND_MENU_EXIT_SUB;
		break;
		

	}
	
	*ret_data=tmp;
      
#if DEBUG == 1
      int k;
      for(k=0; k < 12 ;k++){
        printf("%lf\n" ,  temara_data[k].day_avg );
      }
#endif

	return 0;
}

int main(int argc, const char * argv[]) {
#if DEBUG  == 1
  printf("---start---");
  println();
#endif
  /*変数*/
  int flg_pg=0;
  struct user_input_type user_input;
  struct temparature_type tempara_data_all[INDEX_ALL];
  struct temparature_type tempara_data_2016[INDEX];
  struct temparature_type tempara_data_2015[INDEX];
  struct temparature_type tempara_data_2014[INDEX];
  struct temparature_type tempara_data_2013[INDEX];
  struct temparature_type tempara_data_2012[INDEX];
  struct temparature_type tempara_data_2011[INDEX];
  struct temparature_type tempara_data_2010[INDEX];
  struct temparature_type tempara_data_2009[INDEX];
  struct temparature_type tempara_data_2008[INDEX];
  struct temparature_type tempara_data_2007[INDEX];
  struct temparature_type tempara_data_2006[INDEX];
  struct temparature_type tempara_data_2005[INDEX];
  struct temparature_type tempara_data_2004[INDEX];
  struct temparature_type tempara_data_2003[INDEX];


	int flg_loop_menu=0;
	int flg_loop_monthly=0;
	
	while(1){
		switch(show_menu()){
			case MONTHLY_DATA:
				while(1){
					switch(show_monthly_menu()){
						case AVG_DATA :
						SUBMENU=AVG_DATA;
						break;
						
						case MAX_DATA:
						SUBMENU=MAX_DATA;
						break;
						
						case MIN_DATA:
						SUBMENU=MIN_DATA;
						break;
						
						case ALL_DATA:
						SUBMENU=ALL_DATA;
						break;
						
						case EXIT_SUB:
						SUBMENU=EXIT_SUB;
						break;
						
					}
					if (SUBMENU==EXIT_SUB) break;

					set_input_date(&user_input);
#if DEBUG == 1
					printf("year=%d  month=%d\n",user_input.year, user_input.month);
#endif
					switch(user_input.year){
						case 2016:
						set_tempara_data( tempara_data_2016, "tempara_2016.dat" );
						show_monthly_day_avg(SUBMENU, &user_input, tempara_data_2016);

						break;
					
						case 2015:
						set_tempara_data( tempara_data_2015, "tempara_2015.dat" );
						show_monthly_day_avg(SUBMENU, &user_input, tempara_data_2015);
						break;
					
						case 2014:
						set_tempara_data( tempara_data_2014, "tempara_2014.dat" );
						show_monthly_day_avg(SUBMENU, &user_input, tempara_data_2014);
						break;
					
						case 2013:
						set_tempara_data( tempara_data_2013, "tempara_2013.dat" );
						show_monthly_day_avg(SUBMENU, &user_input, tempara_data_2013);
						break;
					
						case 2012:
						set_tempara_data( tempara_data_2012, "tempara_2012.dat" );
						show_monthly_day_avg(SUBMENU, &user_input, tempara_data_2012);
						break;
					
						case 2011:
						set_tempara_data( tempara_data_2011, "tempara_2011.dat" );
						show_monthly_day_avg(SUBMENU, &user_input, tempara_data_2011);
						break;
					
						case 2010:
						set_tempara_data( tempara_data_2010, "tempara_2010.dat" );
						show_monthly_day_avg(SUBMENU, &user_input, tempara_data_2010);
						break;
					
						case 2009:
						set_tempara_data( tempara_data_2009, "tempara_2009.dat" );
						show_monthly_day_avg(SUBMENU, &user_input, tempara_data_2009);
						break;
					
						case 2008:
						set_tempara_data( tempara_data_2008, "tempara_2008.dat" );
						show_monthly_day_avg(SUBMENU, &user_input, tempara_data_2008);
						break;
					
						case 2007:
						set_tempara_data( tempara_data_2007, "tempara_2007.dat" );
						show_monthly_day_avg(SUBMENU, &user_input, tempara_data_2007);
						break;
					
						case 2006:
						set_tempara_data( tempara_data_2006, "tempara_2006.dat" );
						show_monthly_day_avg(SUBMENU, &user_input, tempara_data_2006);
						break;
					
						case 2005:
						set_tempara_data( tempara_data_2005, "tempara_2005.dat" );
						show_monthly_day_avg(SUBMENU, &user_input, tempara_data_2005);
						break;
					}
					
					while(1){
						printf("Again?[1:Yes/0:No]:");
						scanf("%d", &flg_loop_monthly);
						if(flg_loop_monthly==1 || flg_loop_monthly==0) break;	
					}
					if(flg_loop_monthly==0) 
					break;
				
				}
			break;
			
			case FIND_MAX_DATA:
				/*すべて読んでセットしておく*/
				if(set_tempara_data_all( tempara_data_all, "tempara.dat" )!=0){
					printf("Please set tempara.data.\n");
					return -1;
				}

#if DEBUG  == 1
				printf("Read all the tempara_data\n");
#endif
				/*Sub Menu*/
				SUB_FIND_MENU = show_find_menu();
				/*User Input*/
				set_input_date_period(&user_input);
				//TODO:find_max_dataを呼び出し
				//double max_val;
				//find_max_data(SUB_FIND_MENU, &user_input, tempara_data_all, &max_val);
				find_max_data(SUB_FIND_MENU, &user_input, tempara_data_all);
				
				break;
				
			case COMPUTE_AVG_DATA:
				/*すべて読んでセットしておく*/
				if(set_tempara_data_all( tempara_data_all, "tempara.dat" )!=0){
					printf("Please set tempara.data.\n");
					return -1;
				}
				break;

			}
		
		while(1){
			printf("Do you want to show menu?[1:Yes/0:No]:");
			scanf("%d", &flg_loop_menu);
			if(flg_loop_menu==1 || flg_loop_menu==0) break;	
		}
		if(flg_loop_menu==0) {
			printf("Bye.Bye.\n\n");
			break;
		}
			
	}		
  return 0;
}


int show_menu(void){
  int i_menu;
  int ret;
  while(1){
    printf("=================================================================\n");
    printf("   DISPLAY MONTHLY DATA(presskey:1)       \n");
    printf("   FIND MAX DATA FROM YEAR TO YEAR (presskey:2)        \n");
    printf("   COMPUTE AVG DATA FROM YEAR TO YEAR(presskey:3)\n");
    printf("   Exit(presskey:9)                   \n");
    printf("=================================================================\n");
    printf(":");
    ret = scanf("%d",&i_menu);
#if DEBUG == 1
    println();
    printf("ret=%d", ret);println();
    printf("i_menu=%d", i_menu);println();
    println();
#endif
    if(ret != 1){
      scanf("%*s");
      continue;
    }else{
      if( i_menu == MONTHLY_DATA|| i_menu==FIND_MAX_DATA || i_menu==COMPUTE_AVG_DATA || i_menu == EXIT ){
        return i_menu;
      } else {
        continue;
      }
    }
  }
}

int show_monthly_menu(void){
  int i_menu;
  int ret;
  while(1){
    printf("=================================================================\n");
    printf("   AVG DATA(presskey:1)\n");
    printf("   MAX_DATA(presskey:2)\n");
    printf("   MIN_DATA(presskey:3)\n");
    printf("   ALL_DATA(presskey:4)\n");
	printf("   Exit(presskey:9)\n");
    printf("=================================================================\n");
    printf(":");
    ret = scanf("%d",&i_menu);
#if DEBUG == 1
    println();
    printf("ret=%d", ret);println();
    printf("i_menu=%d", i_menu);println();
    println();
#endif
    if(ret != 1){
      scanf("%*s");
      continue;
    }else{
      if( i_menu == AVG_DATA|| i_menu==MAX_DATA || i_menu==MIN_DATA || i_menu ==ALL_DATA || i_menu == EXIT ){
        return i_menu;
      } else {
        continue;
      }
    }
  }
}


int show_find_menu(void){
  int i_menu;
  int ret;
  while(1){
    printf("=================================================================\n");
    printf("   AVG DATA[AVG DAY](presskey:1)\n");
    printf("   AVG DATA[MAX DAY](presskey:2)\n");
    printf("   AVG DATA[MIN DAY](presskey:3)\n");
    printf("   MAX_DATA(presskey:4)\n");
    printf("   MIN_DATA(presskey:5)\n");
	printf("   Exit(presskey:9)\n");
    printf("=================================================================\n");
    printf(":");
    ret = scanf("%d",&i_menu);
#if DEBUG == 1
    println();
    printf("ret=%d", ret);println();
    printf("i_menu=%d", i_menu);println();
    println();
#endif
    if(ret != 1){
      scanf("%*s");
      continue;
    }else{
	  if( i_menu == FIND_MENU_AGV_DAY  ||  i_menu == FIND_MENU_AGV_MAX  ||
          i_menu == FIND_MENU_AGV_MIN  ||  i_menu == FIND_MENU_MAX_DATA ||
          i_menu == FIND_MENU_MIN_DATA ||  i_menu == EXIT_SUB){
	  return i_menu;
      } else {
        continue;
      }
    }
  }
}


int set_tempara_data(struct temparature_type *tempara_data, char filename[] ){
  int k=0;
  char buf[1000];
  FILE* fp;
  fp = fopen(filename, "r");
  if(fp==NULL){
    printf("File[%s] does not exist.\n", filename );
    return -1;

  }else{
#if DEBUG ==1
    printf("Opened file.\n");
#endif
  }

  while (fgets(buf, 256, fp) != NULL) {

    int ret = sscanf(buf, 
        "%d"  "%lf"  "%lf"  "%lf"  "%lf"  "%lf", 
        &tempara_data[k].month, &tempara_data[k].day_avg, &tempara_data[k].day_max, 
        &tempara_data[k].day_min, &tempara_data[k].month_max, &tempara_data[k].month_min
        );
#if DEBUG ==1
		printf("%d\n",ret);
#endif
    k++;
  }

#if DEBUG  == 1
  for(k=0; k<INDEX ; k++){
    printf("index=%d", k);   
    printf("month=%d \t day_avg=%f \t day_max=%f \t day_min=%f \t month_max=%f \t month_min=%f ", 
    tempara_data[k].month , tempara_data[k].day_avg , tempara_data[k].day_max , tempara_data[k].day_min , tempara_data[k].month_max, tempara_data[k].month_min);
    println();
  }
#endif
  fclose(fp);
  return 0;
}

int set_tempara_data_all(struct temparature_type *tempara_data, char filename[] ){
  int k=0;
  char buf[1000];
  FILE* fp;

  fp = fopen(filename, "r");
  if(fp==NULL){
    printf("File[%s] does not exist.\n", filename);
    return -1;

  }else{
#if DEBUG == 1
	printf("Opened file[%s].\n", filename);
#endif

  }

  
  while (fgets(buf, 256, fp) != NULL) {

    int ret = sscanf(buf, 
        "%d"  "%lf"  "%lf"  "%lf"  "%lf"  "%lf", 
        &tempara_data[k].month, &tempara_data[k].day_avg, &tempara_data[k].day_max, 
        &tempara_data[k].day_min, &tempara_data[k].month_max, &tempara_data[k].month_min
        );//ok
#if DEBUG == 1
	printf("index=%d \t", k);   
    printf("month=%d \t day_avg=%f \t day_max=%f \t day_min=%f \t month_max=%f \t month_min=%f ", 
    tempara_data[k].month , tempara_data[k].day_avg , tempara_data[k].day_max , tempara_data[k].day_min , tempara_data[k].month_max, tempara_data[k].month_min);
    println();
#endif
    k++;
  }

  fclose(fp);
  return 0;
}

int set_input_date( struct user_input_type *user_input){
	int flg_input=0;
    while(1){
		printf("Please input year[yyyy]:");
		flg_input =scanf("%d", &user_input->year);
		if(flg_input != 1){
		  scanf("%*s");
		  continue;
		}else{
		  if( user_input->year >= 2003 &&  user_input->year <= 2016) break;
		  else showErrMsg("year",0.0, user_input->year);
		}
	}
	while(1){
		printf("Please input month[1-12]:");
		flg_input = scanf("%d", &user_input->month);
		if(flg_input != 1){
			scanf("%*s");
			continue;
		}else{
			if( user_input->month > 0 &&  user_input->month < 13 ) break;
			else showErrMsg("month",0.0, user_input->month);
		}
	}
	return 0;
}

int set_input_date_period( struct user_input_type *user_input){
	int flg_input=0;
		//入力を受け付け
		while(1){
				printf("Please input from year[yyyy]:");
				flg_input =scanf("%d", &user_input->from_year);
				if(flg_input != 1){
					scanf("%*s");
					continue;
				}else{
					//TODO:defineにする
					if( user_input->from_year >= 2003 &&  user_input->from_year <= 2016) break;
					else showErrMsg("from year",0.0, user_input->from_year);
			}
		}
		
		while(1){
				printf("Please input to year[yyyy]:");
				flg_input =scanf("%d", &user_input->to_year);
				if(flg_input != 1){
					scanf("%*s");
					continue;
				}else{
						//TODO:defineにする
					if( user_input->to_year >= 2003 &&  user_input->to_year <= 2016) break;
					else showErrMsg("to year",0.0, user_input->to_year);
			}
		}
		
		while(1){
			printf("Please input month[1-12]:");
			flg_input = scanf("%d", &user_input->month);
			if(flg_input != 1){
				scanf("%*s");
				continue;
			}else{
				if( user_input->month > 0 &&  user_input->month < 13 ) break;
				else showErrMsg("month",0.0, user_input->month);
			}
		}

	return 0;
}


//TODO:find_max_data本体 
//TODO:double *ret_data いらない。。。
int find_max_data(int SUB_FIND_MENU_TYPE, struct user_input_type *user_input, struct temparature_type *temara_data  ){
#if DEBUG  == 1
	printf("find_max_data-------------------\n");
#endif
	int wk_from_year = user_input->from_year;
	int period = user_input->from_year - user_input->to_year + 1;
	int i_end = period;
	int i_cnt=0;
	int i=0;
	int i_start= (user_input->month-1) +12*(2016 - wk_from_year );
	char *menu_type;
	
	double max_val=0.0;
	int max_year  = wk_from_year; 
	int max_month = temara_data[i_start].month;

	SUB_FIND_MENU = SUB_FIND_MENU_TYPE;
	switch( SUB_FIND_MENU ){
			case FIND_MENU_AGV_DAY :
#if DEBUG  == 1
				printf("SUB_FIND_MENU=FIND_MENU_AGV_DAY\n");
				printf("Debugging----------------------\n");
				printf("i[=i_start]=%d\n", i_start);
				printf("day_avg[=max_val]=%lf\n", max_val);
				printf("Debugging----------------------\n");
#endif
				menu_type="AVG DATA";
				max_val=temara_data[i_start].day_avg;
       			 while( i_cnt+1 < i_end ){
					--wk_from_year;
        			i=(user_input->month-1) +12*(2016 - wk_from_year ) ;
					if(max_val < temara_data[i].day_avg){
						//find!
						max_year  = wk_from_year; 
						max_month = temara_data[i].month;
						max_val   =temara_data[i].day_avg;
					}

#if DEBUG  == 1
					printf("Debugging----------------------\n");
					printf("day_avg=%lf\n", temara_data[i].day_avg);
  					printf("i_cnt=%d\n", i_cnt);
					printf("i=%d\n", i);
					printf("i_end=%d\n", i_end);
					println();
					printf("Debugging----------------------\n");
  		
#endif
					++i_cnt;
				}
				printf("\n");
				break;
			
			case FIND_MENU_AGV_MAX:
#if DEBUG  == 1
				printf("SUB_FIND_MENU=FIND_MENU_AGV_MAX\n");
				printf("Debugging----------------------\n");
				printf("i[=i_start]=%d\n", i_start);
				printf("day_max[=max_val]=%lf\n", max_val);
				printf("Debugging----------------------\n");
#endif
				menu_type="AVG MAX";
				max_val=temara_data[i_start].day_max;
       			 while( i_cnt+1 < i_end ){
					--wk_from_year;
        			i=(user_input->month-1) +12*(2016 - wk_from_year ) ;
					if(max_val < temara_data[i].day_max){
						max_year  = wk_from_year; 
						max_month = temara_data[i].month;
						max_val=temara_data[i].day_max;
					}

#if DEBUG  == 1
					printf("Debugging----------------------\n");
					printf("day_max=%lf\n", temara_data[i].day_max);
  					printf("i_cnt=%d\n", i_cnt);
					printf("i=%d\n", i);
					printf("i_end=%d\n", i_end);
					println();
					printf("Debugging----------------------\n");
#endif
					++i_cnt;
				}
				break;
			
			case FIND_MENU_AGV_MIN:
#if DEBUG  == 1
				printf("SUB_FIND_MENU=FIND_MENU_AGV_MIN\n");
				printf("Debugging----------------------\n");
				printf("i[=i_start]=%d\n", i_start);
				printf("day_min[=max_val]=%lf\n", max_val);
				printf("Debugging----------------------\n");
#endif
				menu_type="AVG MIN";
				max_val=temara_data[i_start].day_min;
       			 while( i_cnt+1 < i_end ){
					--wk_from_year;
        			i=(user_input->month-1) +12*(2016 - wk_from_year ) ;
					if(max_val < temara_data[i].day_min){
						max_year  = wk_from_year; 
						max_month = temara_data[i].month;
						max_val=temara_data[i].day_min;
					}

#if DEBUG  == 1
					printf("Debugging----------------------\n");
					printf("day_min=%lf\n", temara_data[i].day_min);
  					printf("i_cnt=%d\n", i_cnt);
					printf("i=%d\n", i);
					printf("i_end=%d\n", i_end);
					println();
					printf("Debugging----------------------\n");
#endif
					++i_cnt;
				}
				break;
			
			case FIND_MENU_MAX_DATA:
#if DEBUG  == 1
				printf("SUB_FIND_MENU=FIND_MENU_MAX_DATA\n");
				printf("Debugging----------------------\n");
				printf("i[=i_start]=%d\n", i_start);
				printf("month_max[=max_val]=%lf\n", max_val);
				printf("Debugging----------------------\n");
#endif
				menu_type="MAX_DATA";
				max_val=temara_data[i_start].month_max;
       			 while( i_cnt+1 < i_end ){
					--wk_from_year;
        			i=(user_input->month-1) +12*(2016 - wk_from_year ) ;
					if(max_val < temara_data[i].month_max){
						max_year  = wk_from_year; 
						max_month = temara_data[i].month;
						max_val=temara_data[i].month_max;
					}

#if DEBUG  == 1
					printf("Debugging----------------------\n");
					printf("month_max=%lf\n", temara_data[i].month_max);
  					printf("i_cnt=%d\n", i_cnt);
					printf("i=%d\n", i);
					printf("i_end=%d\n", i_end);
					println();
					printf("Debugging----------------------\n");
#endif
					++i_cnt;
				}
				break;
			
			case FIND_MENU_MIN_DATA:
#if DEBUG  == 1
				printf("SUB_FIND_MENU=FIND_MENU_MIN_DATA\n");
				printf("Debugging----------------------\n");
				printf("i[=i_start]=%d\n", i_start);
				printf("month_min[=max_val]=%lf\n", max_val);
				printf("Debugging----------------------\n");
#endif
				menu_type="MIN_DATA";
				max_val=temara_data[i_start].month_min;
       			 while( i_cnt+1 < i_end ){
					--wk_from_year;
        			i=(user_input->month-1) +12*(2016 - wk_from_year ) ;
					if(max_val < temara_data[i].month_min){
						max_year  = wk_from_year; 
						max_month = temara_data[i].month;
						max_val=temara_data[i].month_min;
					}
#if DEBUG  == 1
					printf("Debugging----------------------\n");
					printf("month_min=%lf\n", temara_data[i].month_min);
  					printf("i_cnt=%d\n", i_cnt);
					printf("i=%d\n", i);
					printf("i_end=%d\n", i_end);
					println();
					printf("Debugging----------------------\n");
#endif
					++i_cnt;
				}
				break;
			
			case FIND_MENU_EXIT_SUB:
			//TODO:いらない？
#if DEBUG  == 1
				printf("SUB_FIND_MENU=FIND_MENU_EXIT_SUB\n");
#endif
				break;
        }
	//TODO:リターンしない？
	//*ret_data=max_val;
	
	printf("--------MAX DATA[%s]-------------\n",menu_type);
	printf("%d/%d\n", max_year,max_month );
	printf("%.2lf\n", max_val );
	printf("---------------------------------\n");
	
	return 0; 
}

int compute_avg_data(int SUB_FIND_MENU_TYPE, struct user_input_type *user_input, struct temparature_type *temara_data  ){
#if DEBUG  == 1
	printf("find_max_data-------------------\n");
#endif
	int wk_from_year = user_input->from_year;
	int period = user_input->from_year - user_input->to_year + 1;
	int i_end = period;
	int i_cnt=0;
	int i=0;
	int i_start= (user_input->month-1) +12*(2016 - wk_from_year );
	char *menu_type;
	
	double max_val=0.0;
	int max_year  = wk_from_year; 
	int max_month = temara_data[i_start].month;

	SUB_FIND_MENU = SUB_FIND_MENU_TYPE;
	switch( SUB_FIND_MENU ){
			case FIND_MENU_AGV_DAY :
#if DEBUG  == 1
				printf("SUB_FIND_MENU=FIND_MENU_AGV_DAY\n");
				printf("Debugging----------------------\n");
				printf("i[=i_start]=%d\n", i_start);
				printf("day_avg[=max_val]=%lf\n", max_val);
				printf("Debugging----------------------\n");
#endif
				menu_type="AVG DATA";
				max_val=temara_data[i_start].day_avg;
       			 while( i_cnt+1 < i_end ){
					--wk_from_year;
        			i=(user_input->month-1) +12*(2016 - wk_from_year ) ;
					if(max_val < temara_data[i].day_avg){
						//find!
						max_year  = wk_from_year; 
						max_month = temara_data[i].month;
						max_val   =temara_data[i].day_avg;
					}

#if DEBUG  == 1
					printf("Debugging----------------------\n");
					printf("day_avg=%lf\n", temara_data[i].day_avg);
  					printf("i_cnt=%d\n", i_cnt);
					printf("i=%d\n", i);
					printf("i_end=%d\n", i_end);
					println();
					printf("Debugging----------------------\n");
  		
#endif
					++i_cnt;
				}
				printf("\n");
				break;
			
			case FIND_MENU_AGV_MAX:
#if DEBUG  == 1
				printf("SUB_FIND_MENU=FIND_MENU_AGV_MAX\n");
				printf("Debugging----------------------\n");
				printf("i[=i_start]=%d\n", i_start);
				printf("day_max[=max_val]=%lf\n", max_val);
				printf("Debugging----------------------\n");
#endif
				menu_type="AVG MAX";
				max_val=temara_data[i_start].day_max;
       			 while( i_cnt+1 < i_end ){
					--wk_from_year;
        			i=(user_input->month-1) +12*(2016 - wk_from_year ) ;
					if(max_val < temara_data[i].day_max){
						max_year  = wk_from_year; 
						max_month = temara_data[i].month;
						max_val=temara_data[i].day_max;
					}

#if DEBUG  == 1
					printf("Debugging----------------------\n");
					printf("day_max=%lf\n", temara_data[i].day_max);
  					printf("i_cnt=%d\n", i_cnt);
					printf("i=%d\n", i);
					printf("i_end=%d\n", i_end);
					println();
					printf("Debugging----------------------\n");
#endif
					++i_cnt;
				}
				break;
			
			case FIND_MENU_AGV_MIN:
#if DEBUG  == 1
				printf("SUB_FIND_MENU=FIND_MENU_AGV_MIN\n");
				printf("Debugging----------------------\n");
				printf("i[=i_start]=%d\n", i_start);
				printf("day_min[=max_val]=%lf\n", max_val);
				printf("Debugging----------------------\n");
#endif
				menu_type="AVG MIN";
				max_val=temara_data[i_start].day_min;
       			 while( i_cnt+1 < i_end ){
					--wk_from_year;
        			i=(user_input->month-1) +12*(2016 - wk_from_year ) ;
					if(max_val < temara_data[i].day_min){
						max_year  = wk_from_year; 
						max_month = temara_data[i].month;
						max_val=temara_data[i].day_min;
					}

#if DEBUG  == 1
					printf("Debugging----------------------\n");
					printf("day_min=%lf\n", temara_data[i].day_min);
  					printf("i_cnt=%d\n", i_cnt);
					printf("i=%d\n", i);
					printf("i_end=%d\n", i_end);
					println();
					printf("Debugging----------------------\n");
#endif
					++i_cnt;
				}
				break;
			
			case FIND_MENU_MAX_DATA:
#if DEBUG  == 1
				printf("SUB_FIND_MENU=FIND_MENU_MAX_DATA\n");
				printf("Debugging----------------------\n");
				printf("i[=i_start]=%d\n", i_start);
				printf("month_max[=max_val]=%lf\n", max_val);
				printf("Debugging----------------------\n");
#endif
				menu_type="MAX_DATA";
				max_val=temara_data[i_start].month_max;
       			 while( i_cnt+1 < i_end ){
					--wk_from_year;
        			i=(user_input->month-1) +12*(2016 - wk_from_year ) ;
					if(max_val < temara_data[i].month_max){
						max_year  = wk_from_year; 
						max_month = temara_data[i].month;
						max_val=temara_data[i].month_max;
					}

#if DEBUG  == 1
					printf("Debugging----------------------\n");
					printf("month_max=%lf\n", temara_data[i].month_max);
  					printf("i_cnt=%d\n", i_cnt);
					printf("i=%d\n", i);
					printf("i_end=%d\n", i_end);
					println();
					printf("Debugging----------------------\n");
#endif
					++i_cnt;
				}
				break;
			
			case FIND_MENU_MIN_DATA:
#if DEBUG  == 1
				printf("SUB_FIND_MENU=FIND_MENU_MIN_DATA\n");
				printf("Debugging----------------------\n");
				printf("i[=i_start]=%d\n", i_start);
				printf("month_min[=max_val]=%lf\n", max_val);
				printf("Debugging----------------------\n");
#endif
				menu_type="MIN_DATA";
				max_val=temara_data[i_start].month_min;
       			 while( i_cnt+1 < i_end ){
					--wk_from_year;
        			i=(user_input->month-1) +12*(2016 - wk_from_year ) ;
					if(max_val < temara_data[i].month_min){
						max_year  = wk_from_year; 
						max_month = temara_data[i].month;
						max_val=temara_data[i].month_min;
					}
#if DEBUG  == 1
					printf("Debugging----------------------\n");
					printf("month_min=%lf\n", temara_data[i].month_min);
  					printf("i_cnt=%d\n", i_cnt);
					printf("i=%d\n", i);
					printf("i_end=%d\n", i_end);
					println();
					printf("Debugging----------------------\n");
#endif
					++i_cnt;
				}
				break;
			
			case FIND_MENU_EXIT_SUB://TODO:いらない？
#if DEBUG  == 1
				printf("SUB_FIND_MENU=FIND_MENU_EXIT_SUB\n");
#endif
				break;
        }
	
	printf("--------AVG DATA[%s]-------------\n",menu_type);
	printf("%d/%d\n", max_year,max_month );
	//printf("%lf\n", *ret_data );
	printf("---------------------------------\n");
	
	return 0; 
}
