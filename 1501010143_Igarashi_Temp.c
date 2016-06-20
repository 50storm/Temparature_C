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
/*
プログラムの処理を簡単にするためにm
ファイルは月ごとにして、月ごとの配列で管理する。



*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG 1
#define println()(printf("\n"))
#define INDEX 12

enum menu {MONTHLY_AVG_DATA = 1 , AVG_DATA_FROM_2015 = 2, DISPLAT_ALL_DATA = 3,  EXIT = 9, ERR = -1  };

/*  prototype functions */

struct temparature_type{
  int month;
  double day_avg;
  double day_max;
  double day_min;
  double month_max;
  double month_min;
};

struct  user_input_type
{
    int year;
    int month;
	int period;
};

int set_tempara_data(struct temparature_type *, char [] );
int show_menu(void);
//int show_monthly_day_avg(struct user_input_type *, struct temparature_type *);


/*
エラー表示
*/
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

int set_input_date( struct user_input_type *user_input){
	int flg_input=0;
    //入力を受け付け
    printf("MONTHLY_AVG_DATA\n");
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


int show_monthly_day_avg( struct user_input_type *user_input , struct temparature_type *temara_data )
{
	  printf("%d\n" , user_input->month);
      printf("-------[%d][%d][Average Temparature of Day]--------------\n",  user_input->year , user_input->month );
      printf("%lf\n" ,  temara_data[user_input->month-1].day_avg );
      printf("---------------------------------------------------------\n");
      
      int i;
      for(i=0; i < 12 ;i++){
        printf("%lf\n" ,  temara_data[i].day_avg );
      }
    
	return 0;
}

int set_input_date_period( struct user_input_type *user_input){
	int flg_input=0;
    //入力を受け付け
    printf("MONTHLY_AVG_DATA\n");
    while(1){
		printf("Please input period:");
		flg_input =scanf("%d", &user_input->period);
		if(flg_input != 1){
		  scanf("%*s");
		  continue;
		}else{
		  if( user_input->period > 1 &&  user_input->period <= 14) break;
		  else showErrMsg("period",0.0, user_input->period);
		}
	}
	/*
	2 :2016-2015
	3 :2016-2014
	4 :2016-2013
	5 :2016-2012
	6 :2016-2011
	7 :2016-2010
	8 :2016-2009
	9 :2016-2008
	10:2016-2007
	11:2016-2006
	12:2016-2005
	13:2016-2004
	14:2016-2003
	*/
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


int main(int argc, const char * argv[]) {
#if DEBUG  == 1
  printf("---start---");
  println();
#endif
  /*変数*/
  int flg_pg=0;
  struct user_input_type user_input;

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

  
  /*ファイルを読み込む*/
/*
  flg_pg=set_tempara_data( tempara_data_2016, "tempara_2016.dat" );
  flg_pg=set_tempara_data( tempara_data_2015, "tempara_2015.dat" );
  flg_pg=set_tempara_data( tempara_data_2014, "tempara_2014.dat" );
  flg_pg=set_tempara_data( tempara_data_2013, "tempara_2013.dat" );
  flg_pg=set_tempara_data( tempara_data_2012, "tempara_2012.dat" );
  flg_pg=set_tempara_data( tempara_data_2011, "tempara_2011.dat" );
  flg_pg=set_tempara_data( tempara_data_2010, "tempara_2010.dat" );
  flg_pg=set_tempara_data( tempara_data_2009, "tempara_2009.dat" );
  flg_pg=set_tempara_data( tempara_data_2008, "tempara_2008.dat" );
  flg_pg=set_tempara_data( tempara_data_2007, "tempara_2007.dat" );
  flg_pg=set_tempara_data( tempara_data_2006, "tempara_2006.dat" );
  flg_pg=set_tempara_data( tempara_data_2005, "tempara_2005.dat" );
  flg_pg=set_tempara_data( tempara_data_2004, "tempara_2004.dat" );
  flg_pg=set_tempara_data( tempara_data_2003, "tempara_2003.dat" );
*/

	int flg_loop_menu=0;
	int flg_loop_monthly_avg_day=0;

	while(1){
		switch(show_menu()){
			case MONTHLY_AVG_DATA:
				while(1){
					set_input_date(&user_input);
					printf("year=%d  month=%d",user_input.year, user_input.month);
					println();
					switch(user_input.year){
						case 2016:
						set_tempara_data( tempara_data_2016, "tempara_2016.dat" );
						show_monthly_day_avg( &user_input, tempara_data_2016);
						break;
					
						case 2015:
						set_tempara_data( tempara_data_2015, "tempara_2015.dat" );
						show_monthly_day_avg( &user_input, tempara_data_2015);
						break;
					
						case 2014:
						set_tempara_data( tempara_data_2014, "tempara_2014.dat" );
						show_monthly_day_avg( &user_input, tempara_data_2014);
						break;
					
						case 2013:
						set_tempara_data( tempara_data_2013, "tempara_2013.dat" );
						show_monthly_day_avg( &user_input, tempara_data_2013);
						break;
					
						case 2012:
						set_tempara_data( tempara_data_2012, "tempara_2012.dat" );
						show_monthly_day_avg( &user_input, tempara_data_2012);
						break;
					
						case 2011:
						set_tempara_data( tempara_data_2011, "tempara_2011.dat" );
						show_monthly_day_avg( &user_input, tempara_data_2011);
						break;
					
						case 2010:
						set_tempara_data( tempara_data_2010, "tempara_2010.dat" );
						show_monthly_day_avg( &user_input, tempara_data_2010);
						break;
					
						case 2009:
						set_tempara_data( tempara_data_2009, "tempara_2009.dat" );
						show_monthly_day_avg( &user_input, tempara_data_2009);
						break;
					
						case 2008:
						set_tempara_data( tempara_data_2008, "tempara_2008.dat" );
						show_monthly_day_avg( &user_input, tempara_data_2008);
						break;
					
						case 2007:
						set_tempara_data( tempara_data_2007, "tempara_2007.dat" );
						show_monthly_day_avg( &user_input, tempara_data_2007);
						break;
					
						case 2006:
						set_tempara_data( tempara_data_2006, "tempara_2006.dat" );
						show_monthly_day_avg( &user_input, tempara_data_2006);
						break;
					
						case 2005:
						set_tempara_data( tempara_data_2005, "tempara_2005.dat" );
						show_monthly_day_avg( &user_input, tempara_data_2005);
						break;
					}
					while(1){
						printf("Again?[1:Yes/0:No]:");
						scanf("%d", &flg_loop_monthly_avg_day);
						if(flg_loop_monthly_avg_day==1 || flg_loop_monthly_avg_day==0) break;	
					}
					if(flg_loop_monthly_avg_day==0) 
					break;
				
				}
			break;
			
			case AVG_DATA_FROM_2015:
				
				set_tempara_data( tempara_data_2016, "tempara_2016.dat" );
				set_tempara_data( tempara_data_2015, "tempara_2015.dat" );
				set_tempara_data( tempara_data_2014, "tempara_2014.dat" );
				set_tempara_data( tempara_data_2013, "tempara_2013.dat" );
				set_tempara_data( tempara_data_2012, "tempara_2012.dat" );
				set_tempara_data( tempara_data_2011, "tempara_2011.dat" );
				set_tempara_data( tempara_data_2010, "tempara_2010.dat" );
				set_tempara_data( tempara_data_2009, "tempara_2009.dat" );
				set_tempara_data( tempara_data_2008, "tempara_2008.dat" );
				set_tempara_data( tempara_data_2007, "tempara_2007.dat" );
				set_tempara_data( tempara_data_2006, "tempara_2006.dat" );
				set_tempara_data( tempara_data_2005, "tempara_2005.dat" );
				set_tempara_data( tempara_data_2004, "tempara_2004.dat" );
				set_tempara_data( tempara_data_2003, "tempara_2003.dat" );
#if DEBUG  == 1
				printf("Read all the tempara_data");
#endif
			
			
				//ユーザーからのインプット情報をセット
				set_input_date_period(&user_input);
				//年の期間
					/*
					2 :2016-2015
					3 :2016-2014
					4 :2016-2013
					5 :2016-2012
					6 :2016-2011
					7 :2016-2010
					8 :2016-2009
					9 :2016-2008
					10:2016-2007
					11:2016-2006
					12:2016-2005
					13:2016-2004
					14:2016-2003
					*/
				switch(user_input.period){
					case 2:
					
					
					
					break;
					
					
					
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


int set_tempara_data(struct temparature_type *tempara_data, char filename[] ){
  int k=0;
  char buf[1000];
  FILE* fp;

  printf("%s\n", filename );
  fp = fopen(filename, "r");
  if(fp==NULL){
    printf("File does not exist.\n");
    return -1;

  }else{
    printf("Opened file.\n");

  }

  while (fgets(buf, 256, fp) != NULL) {

    int ret = sscanf(buf, 
        "%d"  "%lf"  "%lf"  "%lf"  "%lf"  "%lf", 
        &tempara_data[k].month, &tempara_data[k].day_avg, &tempara_data[k].day_max, 
        &tempara_data[k].day_min, &tempara_data[k].month_max, &tempara_data[k].month_min
        );//ok
    printf("%d\n",ret);//6

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

int show_menu(void){
  int i_menu;
  int ret;
  while(1){
    printf("=================================================================\n");
    printf("   Display MONTHLY AVG DATA(presskey:1)       \n");
    printf("   Display AVG_DATA FOR x YEARS FROM 2016 (presskey:2)        \n");
    printf("   Display  ALL BMI DATA / AVG(BMI), SUM and AVG(Steps)(presskey:3)\n");
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
      if( i_menu == MONTHLY_AVG_DATA|| i_menu==AVG_DATA_FROM_2015 || i_menu==DISPLAT_ALL_DATA || i_menu == EXIT ){
        return i_menu;
      } else {
        continue;
      }
    }
  }
}
