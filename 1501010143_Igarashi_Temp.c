/*

今回でC言語の学習は終了し、次回から検索や並べ替えのアルゴリズムの実装にとりか かります。そこで、今回はこれまでに学習したことの総まとめとして、条件分岐、繰り返し、 配列、関数、など学んだことを駆使して、過去数十年間の月別平均気温のデータをファイル から配列に読み込み、下記の1~6に沿って各自でそのデータを利用したオリジナルのプ ログラムを作成してください。
1 少なくとも過去10年分以上のデータを読み込む。 第7回配布のサンプルでは東京の 2000 年~2013 年の 14 年間のデータを使用しまし たので、そのまま利用しても構いませんが、次ページの「使用する平均気温データに ついて」を参考にして自分の住んでいる地域の過去 100 年分あるいは観測開始以来の 全ての年などを読み込んでみるのも面白いでしょう。
2 キーボードから指定した○年△月のデータを表示する。 これもサンプルファイルを実行するだけで出来ますが、1 度だけでなく何度もこの機 能を繰り返せるようにするとか、2000 年より以前のデータも読み込んでおき配列の 要素番号と西暦年の対応を考えて取り組むなど、いろいろ工夫も出来そうです。
3 キーボードから指定した月について、読み込んだ全期間あるいは 10 年間の平均を計 算し表示すること。
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

enum menu {MONTHLY_AVG_DATA = 1 , DISPLAY_DATA = 2, DISPLAT_ALL_DATA = 3,  EXIT = 9, ERR = -1  };

/*  prototype functions */

struct temparature_type{
  int month;
  double day_avg;
  double day_max;
  double day_min;
  double month_max;
  double month_min;
};

int set_tempara_data(struct temparature_type *, char [] );

int show_menu(void){
  int i_menu;
  int ret;
  while(1){
    printf("=================================================================\n");
    printf("   Display MONTHLY AVG DATA(presskey:1)      \n");
    printf("   Display BMI DATA(presskey:2)        \n");
    printf("   Display  ALL BMI DATA / AVG(BMI), SUM and AVG(Steps)(presskey:3)\n");
    printf("   Exit(presskey:9)                   \n");
    printf("=================================================================\n");
    printf(":");
    ret = scanf("%d",&i_menu);
#if DEBUG  == 1
    println();
    printf("%d", ret);println();
    printf("%d", i_menu);println();
    println();
#endif
    if(ret != 1){
      scanf("%*s");
      continue;
    }else{
      if( i_menu == MONTHLY_AVG_DATA|| i_menu==DISPLAY_DATA || i_menu==DISPLAT_ALL_DATA || i_menu == EXIT ){
        return i_menu;
      } else {
        continue;
      }
    }
  }
}

int main(int argc, const char * argv[]) {
#if DEBUG  == 1
  printf("---start---");
  println();
#endif
  int flg_pg=0;
  struct temparature_type *tempara_p;
/*
Segmentation fault: 11
スタック領域に入らないようだ。。。
*/
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
  struct temparature_type tempara_data_2002[INDEX];
  struct temparature_type tempara_data_2001[INDEX];
  struct temparature_type tempara_data_2000[INDEX];

  flg_pg=set_tempara_data( tempara_data_2015, "tempara_2015.dat" );
  flg_pg=set_tempara_data( tempara_data_2014, "tempara_2014.dat"  );
  flg_pg=set_tempara_data( tempara_data_2013, "tempara_2013.dat"  );
  flg_pg=set_tempara_data( tempara_data_2012, "tempara_2012.dat"  );
  
  /*
  char *filename="tempara_2011.dat";
  flg_pg=set_tempara_data( tempara_data_2011, filename );

  flg_pg=set_tempara_data( tempara_data_2010, filename );
  flg_pg=set_tempara_data( tempara_data_2009, filename );
  flg_pg=set_tempara_data( tempara_data_2008, filename );
*/

      //n個分のメモリを確保する
  /*
    int n=1;

    tempara_p = malloc( sizeof(struct temparature_type ) * n );
    if (tempara_p == NULL) {
        printf( "memory allocation error\n" );
        exit(EXIT_FAILURE);
    }
  flg_pg=set_tempara_data( tempara_p, filename );
  
*/

  
  
 
  return 0;
}

int set_tempara_data(struct temparature_type *tempara_data, char filename[] ){
  int k=0;
  char buf[1000];
  FILE* fp;

/*
  for(k=0; k<INDEX ; k++){
    printf("%d\n",k);

    tempara_data[k].month     =0   ;
    tempara_data[k].day_avg   =0.0 ;
    tempara_data[k].day_max   =0.0;
    tempara_data[k].day_min   =0.0 ;
    tempara_data[k].month_max =0.0 ;
    tempara_data[k].month_min =0.0;

  }
  */

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
