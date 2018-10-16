#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <time.h>
#include <math.h>
#include "linkedlist.h"
#include <omp.h>
#include <string.h>
#include "linked_list_test_framework/test_framework.h"
#include "linked_list_test_framework/maple_evaluate.h"

#include <unistd.h> //sleep

#ifdef __cplusplus
extern "C" {
#endif

linked_list_q *test_100(){
    linked_list_q *list = create_linked_list_q();
    int m_vars = 3;
    
    term_q* l0 = create_term_str_q("1861906/725545",3,2092,3649,5005);
    linked_list_tail_insert_q(list,NULL,l0);

    term_q* l1 = create_term_str_q("1744344/917871",3,5685,2549,5024);
    linked_list_tail_insert_q(list,NULL,l1);

    term_q* l2 = create_term_str_q("427843/460820",3,1534,1376,24);
    linked_list_tail_insert_q(list,NULL,l2);

    term_q* l3 = create_term_str_q("1476605/179365",3,4341,1346,1974);
    linked_list_tail_insert_q(list,NULL,l3);

    term_q* l4 = create_term_str_q("480873/964910",3,2602,144,1753);
    linked_list_tail_insert_q(list,NULL,l4);

    term_q* l5 = create_term_str_q("1276644/633301",3,3763,5737,5300);
    linked_list_tail_insert_q(list,NULL,l5);

    term_q* l6 = create_term_str_q("214807/243709",3,4079,2925,2549);
    linked_list_tail_insert_q(list,NULL,l6);

    term_q* l7 = create_term_str_q("1035782/685152",3,5507,5319,4799);
    linked_list_tail_insert_q(list,NULL,l7);

    term_q* l8 = create_term_str_q("827823/204403",3,3181,1586,1854);
    linked_list_tail_insert_q(list,NULL,l8);

    term_q* l9 = create_term_str_q("1702598/371989",3,1458,517,3317);
    linked_list_tail_insert_q(list,NULL,l9);

    term_q* l10 = create_term_str_q("1023503/601473",3,4884,5145,1254);
    linked_list_tail_insert_q(list,NULL,l10);

    term_q* l11 = create_term_str_q("1191366/38469",3,5198,1650,5969);
    linked_list_tail_insert_q(list,NULL,l11);

    term_q* l12 = create_term_str_q("398327/749454",3,2862,1427,5769);
    linked_list_tail_insert_q(list,NULL,l12);

    term_q* l13 = create_term_str_q("101900/55281",3,5050,4668,4917);
    linked_list_tail_insert_q(list,NULL,l13);

    term_q* l14 = create_term_str_q("243664/556892",3,1528,2883,1720);
    linked_list_tail_insert_q(list,NULL,l14);

    term_q* l15 = create_term_str_q("355266/996311",3,3284,2147,1386);
    linked_list_tail_insert_q(list,NULL,l15);

    term_q* l16 = create_term_str_q("1570651/947421",3,4716,342,5952);
    linked_list_tail_insert_q(list,NULL,l16);

    term_q* l17 = create_term_str_q("329929/564565",3,5352,1748,1650);
    linked_list_tail_insert_q(list,NULL,l17);

    term_q* l18 = create_term_str_q("1149610/637174",3,4850,40,3140);
    linked_list_tail_insert_q(list,NULL,l18);

    term_q* l19 = create_term_str_q("563922/600123",3,5676,485,2421);
    linked_list_tail_insert_q(list,NULL,l19);

    term_q* l20 = create_term_str_q("594312/692390",3,3776,3338,3144);
    linked_list_tail_insert_q(list,NULL,l20);

    term_q* l21 = create_term_str_q("1278974/858946",3,2669,2601,4195);
    linked_list_tail_insert_q(list,NULL,l21);

    term_q* l22 = create_term_str_q("0",3,245,3542,3283);
    linked_list_tail_insert_q(list,NULL,l22);

    term_q* l23 = create_term_str_q("1708760/12771",3,3292,5644,736);
    linked_list_tail_insert_q(list,NULL,l23);

    term_q* l24 = create_term_str_q("1126045/735830",3,2289,916,3877);
    linked_list_tail_insert_q(list,NULL,l24);

    term_q* l25 = create_term_str_q("909862/211451",3,4835,3527,3917);
    linked_list_tail_insert_q(list,NULL,l25);

    term_q* l26 = create_term_str_q("0",3,125,2948,635);
    linked_list_tail_insert_q(list,NULL,l26);

    term_q* l27 = create_term_str_q("703292/866686",3,5225,4394,5485);
    linked_list_tail_insert_q(list,NULL,l27);

    term_q* l28 = create_term_str_q("1663332/436870",3,4078,1814,1277);
    linked_list_tail_insert_q(list,NULL,l28);

    term_q* l29 = create_term_str_q("1029178/789307",3,5254,1119,4757);
    linked_list_tail_insert_q(list,NULL,l29);

    term_q* l30 = create_term_str_q("1639233/41560",3,520,3169,568);
    linked_list_tail_insert_q(list,NULL,l30);

    term_q* l31 = create_term_str_q("441028/951155",3,5625,3375,5766);
    linked_list_tail_insert_q(list,NULL,l31);

    term_q* l32 = create_term_str_q("309616/321807",3,3928,5445,1786);
    linked_list_tail_insert_q(list,NULL,l32);

    term_q* l33 = create_term_str_q("27052/358280",3,1249,5850,79);
    linked_list_tail_insert_q(list,NULL,l33);

    term_q* l34 = create_term_str_q("77696/737646",3,3591,4731,430);
    linked_list_tail_insert_q(list,NULL,l34);

    term_q* l35 = create_term_str_q("79074/654772",3,901,5636,3126);
    linked_list_tail_insert_q(list,NULL,l35);

    term_q* l36 = create_term_str_q("1760374/950610",3,2794,5491,4279);
    linked_list_tail_insert_q(list,NULL,l36);

    term_q* l37 = create_term_str_q("524497/910741",3,1427,1214,4690);
    linked_list_tail_insert_q(list,NULL,l37);

    term_q* l38 = create_term_str_q("726688/485775",3,5562,526,799);
    linked_list_tail_insert_q(list,NULL,l38);

    term_q* l39 = create_term_str_q("1362683/814504",3,5584,4665,5904);
    linked_list_tail_insert_q(list,NULL,l39);

    term_q* l40 = create_term_str_q("636634/557873",3,3788,776,127);
    linked_list_tail_insert_q(list,NULL,l40);

    term_q* l41 = create_term_str_q("1083446/123118",3,2040,4583,2575);
    linked_list_tail_insert_q(list,NULL,l41);

    term_q* l42 = create_term_str_q("274378/334780",3,3607,3810,2498);
    linked_list_tail_insert_q(list,NULL,l42);

    term_q* l43 = create_term_str_q("1247841/873696",3,4347,5200,4383);
    linked_list_tail_insert_q(list,NULL,l43);

    term_q* l44 = create_term_str_q("1897115/384758",3,5470,5727,623);
    linked_list_tail_insert_q(list,NULL,l44);

    term_q* l45 = create_term_str_q("1219936/769824",3,5865,671,2712);
    linked_list_tail_insert_q(list,NULL,l45);

    term_q* l46 = create_term_str_q("1185035/667290",3,4507,2263,227);
    linked_list_tail_insert_q(list,NULL,l46);

    term_q* l47 = create_term_str_q("973741/999568",3,5415,720,4898);
    linked_list_tail_insert_q(list,NULL,l47);

    term_q* l48 = create_term_str_q("832496/301054",3,1604,3456,4577);
    linked_list_tail_insert_q(list,NULL,l48);

    term_q* l49 = create_term_str_q("1634993/67779",3,3562,5925,1602);
    linked_list_tail_insert_q(list,NULL,l49);

    term_q* l50 = create_term_str_q("570615/503011",3,5740,984,1445);
    linked_list_tail_insert_q(list,NULL,l50);

    term_q* l51 = create_term_str_q("1959217/556246",3,3229,1796,4439);
    linked_list_tail_insert_q(list,NULL,l51);

    term_q* l52 = create_term_str_q("1307076/31282",3,2948,3759,5565);
    linked_list_tail_insert_q(list,NULL,l52);

    term_q* l53 = create_term_str_q("1067320/472128",3,4394,2379,2150);
    linked_list_tail_insert_q(list,NULL,l53);

    term_q* l54 = create_term_str_q("1320086/428970",3,2884,5058,2439);
    linked_list_tail_insert_q(list,NULL,l54);

    term_q* l55 = create_term_str_q("289076/979694",3,5339,5808,2200);
    linked_list_tail_insert_q(list,NULL,l55);

    term_q* l56 = create_term_str_q("262457/556830",3,4898,5031,5207);
    linked_list_tail_insert_q(list,NULL,l56);

    term_q* l57 = create_term_str_q("1537736/845390",3,5245,3467,915);
    linked_list_tail_insert_q(list,NULL,l57);

    term_q* l58 = create_term_str_q("1533458/921379",3,1379,574,1162);
    linked_list_tail_insert_q(list,NULL,l58);

    term_q* l59 = create_term_str_q("1677309/604174",3,4502,1587,2955);
    linked_list_tail_insert_q(list,NULL,l59);

    term_q* l60 = create_term_str_q("6216/709165",3,2181,2879,2747);
    linked_list_tail_insert_q(list,NULL,l60);

    term_q* l61 = create_term_str_q("998102/833432",3,2853,3863,3654);
    linked_list_tail_insert_q(list,NULL,l61);

    term_q* l62 = create_term_str_q("1335077/967602",3,2229,5896,352);
    linked_list_tail_insert_q(list,NULL,l62);

    term_q* l63 = create_term_str_q("920105/285311",3,5706,4259,5523);
    linked_list_tail_insert_q(list,NULL,l63);

    term_q* l64 = create_term_str_q("581814/487530",3,1468,3155,2638);
    linked_list_tail_insert_q(list,NULL,l64);

    term_q* l65 = create_term_str_q("1982901/324091",3,244,3235,3555);
    linked_list_tail_insert_q(list,NULL,l65);

    term_q* l66 = create_term_str_q("1307499/560432",3,177,2442,4565);
    linked_list_tail_insert_q(list,NULL,l66);

    term_q* l67 = create_term_str_q("1623991/538782",3,5292,132,4262);
    linked_list_tail_insert_q(list,NULL,l67);

    term_q* l68 = create_term_str_q("877864/378801",3,2133,4777,5607);
    linked_list_tail_insert_q(list,NULL,l68);

    term_q* l69 = create_term_str_q("1743770/517933",3,3789,1984,1917);
    linked_list_tail_insert_q(list,NULL,l69);

    term_q* l70 = create_term_str_q("225117/531232",3,2580,2074,2731);
    linked_list_tail_insert_q(list,NULL,l70);

    term_q* l71 = create_term_str_q("567621/4360",3,811,5718,4956);
    linked_list_tail_insert_q(list,NULL,l71);

    term_q* l72 = create_term_str_q("755523/852108",3,1109,1366,1424);
    linked_list_tail_insert_q(list,NULL,l72);

    term_q* l73 = create_term_str_q("159788/829832",3,1072,1960,4034);
    linked_list_tail_insert_q(list,NULL,l73);

    term_q* l74 = create_term_str_q("195161/758071",3,5547,5014,498);
    linked_list_tail_insert_q(list,NULL,l74);

    term_q* l75 = create_term_str_q("912597/900026",3,2894,121,865);
    linked_list_tail_insert_q(list,NULL,l75);

    term_q* l76 = create_term_str_q("1214883/317805",3,1071,3622,2480);
    linked_list_tail_insert_q(list,NULL,l76);

    term_q* l77 = create_term_str_q("1739666/735052",3,3546,864,1481);
    linked_list_tail_insert_q(list,NULL,l77);

    term_q* l78 = create_term_str_q("1398485/557116",3,3516,2131,4119);
    linked_list_tail_insert_q(list,NULL,l78);

    term_q* l79 = create_term_str_q("448516/615629",3,5575,2471,4955);
    linked_list_tail_insert_q(list,NULL,l79);

    term_q* l80 = create_term_str_q("1118471/63821",3,3295,4119,684);
    linked_list_tail_insert_q(list,NULL,l80);

    term_q* l81 = create_term_str_q("950363/251975",3,5714,3136,2573);
    linked_list_tail_insert_q(list,NULL,l81);

    term_q* l82 = create_term_str_q("139772/787557",3,1266,978,1831);
    linked_list_tail_insert_q(list,NULL,l82);

    term_q* l83 = create_term_str_q("723895/478928",3,1636,5557,3874);
    linked_list_tail_insert_q(list,NULL,l83);

    term_q* l84 = create_term_str_q("1533/797423",3,296,4752,1658);
    linked_list_tail_insert_q(list,NULL,l84);

    term_q* l85 = create_term_str_q("1161596/901785",3,708,4629,4104);
    linked_list_tail_insert_q(list,NULL,l85);

    term_q* l86 = create_term_str_q("1651828/933280",3,999,5783,2025);
    linked_list_tail_insert_q(list,NULL,l86);

    term_q* l87 = create_term_str_q("1971704/952913",3,5012,1926,1824);
    linked_list_tail_insert_q(list,NULL,l87);

    term_q* l88 = create_term_str_q("855934/399877",3,2675,399,142);
    linked_list_tail_insert_q(list,NULL,l88);

    term_q* l89 = create_term_str_q("317415/457965",3,4470,1836,5418);
    linked_list_tail_insert_q(list,NULL,l89);

    term_q* l90 = create_term_str_q("1587851/527774",3,156,3383,1758);
    linked_list_tail_insert_q(list,NULL,l90);

    term_q* l91 = create_term_str_q("-1587851/527774",3,156,3383,1758);
    linked_list_tail_insert_q(list,NULL,l91);

    term_q* l92 = create_term_str_q("998538/299541",3,5807,4040,328);
    linked_list_tail_insert_q(list,NULL,l92);

    term_q* l93 = create_term_str_q("902627/584128",3,1269,838,4437);
    linked_list_tail_insert_q(list,NULL,l93);

    term_q* l94 = create_term_str_q("381423/733283",3,3227,1769,298);
    linked_list_tail_insert_q(list,NULL,l94);

    term_q* l95 = create_term_str_q("1150897/442676",3,5305,3037,2648);
    linked_list_tail_insert_q(list,NULL,l95);

    term_q* l96 = create_term_str_q("709379/381566",3,5071,3504,2543);
    linked_list_tail_insert_q(list,NULL,l96);

    term_q* l97 = create_term_str_q("607100/444093",3,5978,4181,3953);
    linked_list_tail_insert_q(list,NULL,l97);

    term_q* l98 = create_term_str_q("1104444/130660",3,3279,2670,278);
    linked_list_tail_insert_q(list,NULL,l98);

    term_q* l99 = create_term_str_q("1751577/715116",3,4303,4463,306);
    linked_list_tail_insert_q(list,NULL,l99);
    
    return list;
}

linked_list_q* test_create_linked_list_q(){
    linked_list_q *m_list = create_linked_list_q();
    int m_vars = 3;
    
    term_q *m1 = create_term_str_q("57575/11", m_vars, 99443, 11, 11);
    linked_list_tail_insert_q(m_list, NULL, m1);
    
    term_q *m2 = create_term_str_q("-57575/11", m_vars, 433, 4, 11);
    linked_list_tail_insert_q(m_list, NULL, m2);
    
    term_q *m3 = create_term_str_q("3/34333", m_vars, 55, 55, 55);
    linked_list_tail_insert_q(m_list, NULL, m3);
    
    term_q *m4 = create_term_str_q("3655/9", m_vars, 55, 55, 55);
    linked_list_tail_insert_q(m_list, NULL, m4);
    
    term_q *m5= create_term_str_q("98887776/34333", m_vars, 14, 13, 12);
    linked_list_tail_insert_q(m_list, NULL, m5);
    
    term_q *m6 = create_term_str_q("8/171", m_vars, 11, 3, 11);
    linked_list_tail_insert_q(m_list, NULL, m6);
    
    term_q *m7 = create_term_str_q("-6/11", m_vars, 8, 5, 11);
    linked_list_tail_insert_q(m_list, NULL, m7);
    
    term_q *m8 = create_term_str_q("36/34333", m_vars, 55, 9, 55);
    linked_list_tail_insert_q(m_list, NULL, m8);
    
    term_q *m9 = create_term_str_q("77/3", m_vars, 6, 55, 55);
    linked_list_tail_insert_q(m_list, NULL, m9);
    
    term_q *m10= create_term_str_q("6/6", m_vars, 6, 13, 12);
    linked_list_tail_insert_q(m_list, NULL, m10);
    
    term_q *m11= create_term_str_q("6/5", m_vars, 14, 13, 12);
    linked_list_tail_insert_q(m_list, NULL, m11);
    
    term_q *m12 = create_term_str_q("4/171", m_vars, 887, 3, 11);
    linked_list_tail_insert_q(m_list, NULL, m12);
    
    term_q *m13 = create_term_str_q("4/11", m_vars, 6, 5, 1);
    linked_list_tail_insert_q(m_list, NULL, m13);
    
    term_q *m14 = create_term_str_q("5/55", m_vars, 2, 9, 55);
    linked_list_tail_insert_q(m_list, NULL, m14);
    
    term_q *m15 = create_term_str_q("4/943", m_vars, 6, 3, 55);
    linked_list_tail_insert_q(m_list, NULL, m15);
    
    term_q *m16= create_term_str_q("5/44", m_vars, 5, 13, 12);
    linked_list_tail_insert_q(m_list, NULL, m16);
        
    term_q *m17 = create_term_str_q("36/34333", m_vars, 1, 9, 55);
    linked_list_tail_insert_q(m_list, NULL, m17);
    
    term_q *m18 = create_term_str_q("77/3", m_vars, 1, 1, 55);
    linked_list_tail_insert_q(m_list, NULL, m18);
    
    term_q *m19= create_term_str_q("6/6", m_vars, 2, 2, 2);
    linked_list_tail_insert_q(m_list, NULL, m19);
    
    term_q *m20 = create_term_str_q("6/5", m_vars, 2, 3, 3);
    linked_list_tail_insert_q(m_list, NULL, m20);
    
    term_q *m22 = create_term_str_q("4/171", m_vars, 8, 3, 11);
    linked_list_tail_insert_q(m_list, NULL, m22);
    
    term_q *m23 = create_term_str_q("4/11", m_vars, 8, 5, 1);
    linked_list_tail_insert_q(m_list, NULL, m23);
    
    term_q *m24 = create_term_str_q("5/55", m_vars, 999, 9, 4444);
    linked_list_tail_insert_q(m_list, NULL, m24);
    
    term_q *m25 = create_term_str_q("4/943", m_vars, 66, 3, 3);
    linked_list_tail_insert_q(m_list, NULL, m25);
    
    term_q *m26= create_term_str_q("5/44", m_vars, 22, 66, 2);
    linked_list_tail_insert_q(m_list, NULL, m26);
    
    term_q *m27= create_term_str_q("6/4", m_vars, 7765, 2, 2);
    linked_list_tail_insert_q(m_list, NULL, m27);
    
    term_q *m28 = create_term_str_q("443/5", m_vars, 2, 55, 3);
    linked_list_tail_insert_q(m_list, NULL, m28);
    
    term_q *m29 = create_term_str_q("9/171", m_vars, 8, 544, 11);
    linked_list_tail_insert_q(m_list, NULL, m29);
    
    term_q *m30 = create_term_str_q("777/11", m_vars, 8, 5, 1);
    linked_list_tail_insert_q(m_list, NULL, m30);
    
    term_q *m31 = create_term_str_q("44/55", m_vars, 43333, 9, 4444);
    linked_list_tail_insert_q(m_list, NULL, m31);
    
    term_q *m32 = create_term_str_q("42/943", m_vars, 6446, 3, 3);
    linked_list_tail_insert_q(m_list, NULL, m32);
    
    term_q *m33= create_term_str_q("5/44", m_vars, 777, 66, 2);
    linked_list_tail_insert_q(m_list, NULL, m33);
    
    term_q *m34 = create_term_str_q("554/55", m_vars, 4, 9, 4444);
    linked_list_tail_insert_q(m_list, NULL, m34);
    
    term_q *m35 = create_term_str_q("8882/943", m_vars, 5, 321, 3);
    linked_list_tail_insert_q(m_list, NULL, m35);
    
    term_q *m36= create_term_str_q("994/77", m_vars, 3, 99, 2);
    linked_list_tail_insert_q(m_list, NULL, m36);
    
    term_q *m37= create_term_str_q("3444/77", m_vars, 32, 3, 55);
    linked_list_tail_insert_q(m_list, NULL, m37);
    
    return m_list;
}

linked_list_q* generate_8_linked_list_manually(){
    linked_list_q *m_list = create_linked_list_q();
    int m_vars = 3;
    
    term_q *m1 = create_term_str_q("57575/11", m_vars, 99443, 11, 11);
    linked_list_tail_insert_q(m_list, NULL, m1);
    
    term_q *m7 = create_term_str_q("-6/11", m_vars, 8, 5, 11);
    linked_list_tail_insert_q(m_list, NULL, m7);
    
    term_q *m2 = create_term_str_q("-57575/11", m_vars, 433, 4, 11);
    linked_list_tail_insert_q(m_list, NULL, m2);
    
    term_q *m3 = create_term_str_q("3/34333", m_vars, 55, 55, 55);
    linked_list_tail_insert_q(m_list, NULL, m3);
    
    term_q *m4 = create_term_str_q("3655/9", m_vars, 55, 55, 55);
    linked_list_tail_insert_q(m_list, NULL, m4);
    
    term_q *m5= create_term_str_q("98887776/34333", m_vars, 14, 13, 12);
    linked_list_tail_insert_q(m_list, NULL, m5);
    
    term_q *m6 = create_term_str_q("8777777788888/171", m_vars, 11, 3, 11);
    linked_list_tail_insert_q(m_list, NULL, m6);
    
    term_q *m8 = create_term_str_q("36/34333", m_vars, 55, 9, 55);
    linked_list_tail_insert_q(m_list, NULL, m8);
    
    term_q *m9 = create_term_str_q("77/3", m_vars, 6, 55, 55);
    linked_list_tail_insert_q(m_list, NULL, m9);
    
    term_q *m10 = create_term_str_q("77/3", m_vars, 7, 7, 7);
    linked_list_tail_insert_q(m_list, NULL, m10);
    
    term_q *m11 = create_term_str_q("-77/3", m_vars, 7, 7, 7);
    linked_list_tail_insert_q(m_list, NULL, m11);
       
    return m_list;
}

void test_generate_long_long_unsigned_int_degrees_with_values(){
    //create a term manually
    mpq_t c;
    create_mpq_t(&c, 4, 5);
    int num_vars = 3;
    degrees *d = generate_long_long_unsigned_int_degrees_with_values(num_vars, 55, 44, 22);
    term_q *t = create_term_q(c, d, num_vars);
    print_term_q(t, num_vars);    
    return;
}

void test_compare_degrees(){
    int num_vars = 3;
    linked_list_q *temp = create_linked_list_q();
    term_q *t6 = create_term_str_q("44/399", num_vars, 33, 6, 23);
    linked_list_insert_q(temp, NULL, t6);
    
    term_q *t7 = create_term_str_q("77/6", num_vars, 7, 45, 999);
    linked_list_insert_q(temp, NULL, t7);
    //-------------------------------------------------------------------------
    
    //compare and test term degree
    int cmp = compare_degrees(t6->deg, t7->deg, num_vars);
    printf("compare: %d\n", cmp);
    linked_list_destroy_q(temp);
    return;
}

void test_is_linked_list_empty(){
     //check if a linked list is empty
    linked_list_q *test = create_linked_list_q();    
    printf("test empty: %d\n", is_linked_list_empty(test));
    return;
}

void test_linked_list_merge_sort(){
    //------------------------------------------------------------------------
    //create and initialize linked list
    linked_list_q *temp = (linked_list_q*)malloc(sizeof(linked_list_q));
    linked_list_init_q(temp);
    int num_vars = 3;
    
    //----------------------------------------------------------------------
    //create a term using the provided function
    term_q *t2 = create_term_str_q("4/77", num_vars, 5, 4, 11);
    linked_list_insert_q(temp, NULL, t2);
    
    term_q *t3 = create_term_str_q("9/7", num_vars, 1, 8, 2);
    linked_list_insert_q(temp, NULL, t3);
    
    term_q *t4 = create_term_str_q("5/5", num_vars, 877, 0, 1);
    linked_list_insert_q(temp, NULL, t4);
    
    term_q *t5 = create_term_str_q("2/3", num_vars, 5555, 3233, 7765);
    linked_list_insert_q(temp, NULL, t5);
    
    term_q *t6 = create_term_str_q("44/399", num_vars, 33, 6, 23);
    linked_list_insert_q(temp, NULL, t6);
    
    term_q *t7 = create_term_str_q("77/6", num_vars, 7, 45, 999);
    linked_list_insert_q(temp, NULL, t7);
    //-------------------------------------------------------------------------
    
    
    printf("BEFORE temp:   ");
    linked_list_print_q(temp, num_vars);
    printf("\n\n");
    
    linked_list_update_degrees_q(temp, &num_vars, 9);
    
    printf("after degrees update temp:   ");
    linked_list_print_q(temp, num_vars);
    printf("\n\n");
    
    //free or destroy a linked list
    linked_list_destroy_q(temp);
    //--------------------------------------------------------------------------
    
}

void test_build_max_heap(char *test_file, int num_vars){
    linked_list_q* list = generate_linked_list_from_csv_file(test_file);
    printf("list size: %d\n", list->size);
    int list_size = list->size;
    int heap_size = list->size;

    term_q **temp_list = malloc(heap_size*sizeof(term_q*));    
    if(!temp_list){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    double s, t;
    s= omp_get_wtime();
    for(int i =0; i<list_size; i++){
        temp_list[i] = list->head;
        list->head = list->head->next;
        temp_list[i]->next = NULL;
        list->size--;
    }
    free(list);
    t = omp_get_wtime() - s;
    printf("loop: %.10f\n", t);

    s= omp_get_wtime();
    build_max_heap(temp_list, num_vars, heap_size);
    for(int i=0; i<list_size; i++){
        free_linked_list_term_q(temp_list[i]);
    }
    free(temp_list);
}

void test_build_min_heap(char* test_file, int num_vars){
    linked_list_q* list = generate_linked_list_from_csv_file(test_file);
    printf("list size: %d\n", list->size);
    int list_size = list->size;
    int heap_size = list->size;

    term_q **temp_list = malloc(heap_size*sizeof(term_q*));    
    if(!temp_list){
        error_print(error_get_string(ERROR_BAD_ALLOC), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    double s, t;
    s= omp_get_wtime();
    for(int i =0; i<list_size; i++){
        temp_list[i] = list->head;
        list->head = list->head->next;
        temp_list[i]->next = NULL;
        list->size--;
    }
    free(list);
    t = omp_get_wtime() - s;
    printf("loop: %.10f\n", t);

    s= omp_get_wtime();
    build_min_heap(temp_list, num_vars, heap_size);
    for(int i=0; i<list_size; i++){
        free_linked_list_term_q(temp_list[i]);
    }
    free(temp_list);
}

void test_min_heap_sort(char *test_file, int num_vars){
    linked_list_q* list = generate_linked_list_from_csv_file(test_file);
    printf("list size: %d\n", list->size);
    double s, t;

    s= omp_get_wtime();
    linked_list_q *ret =  min_heap_sort(list, num_vars);
    t = omp_get_wtime() - s;
    printf("build: %.10f\n", t);
    free(ret);
    free(list);
}

void test_max_heap_sort(char *test_file, int num_vars){
    linked_list_q* list = generate_linked_list_from_csv_file(test_file);
    printf("list size: %d\n", list->size);
    double s, t;

    s= omp_get_wtime();
    max_heap_sort(list, num_vars);
    t = omp_get_wtime() - s;
    printf("build: %.10f\n", t);
    linked_list_print_q(list, num_vars);
    linked_list_destroy_q(list);
}

void record_time_to_file(char *filename, bool title, int list_size, long int base_case_size, char* k_merge_type, int parallel, double time){
    FILE *f = fopen(filename, "a");
    if(!f){
        error_print(error_get_string(ERROR_FILE_OPEN), __FILE__, __func__, __LINE__);
        exit(ERROR_FAILURE);
    }
    if(title){
        fprintf(f, "%s,%s,%s,%s,%s\n", "list_size", "base_case_size", "k_merge_type", "parallel", "time");
    }else{
        fprintf(f, "%d,%ld,%s,%d,%.10f\n", list_size, base_case_size, k_merge_type, parallel, time);
    }
    fclose(f);
}

void test_linked_list_4_way_heap_merge_sort_parallel_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 4-way parallel heap linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_4_way_heap_merge_sort_parallel_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "4-way-heap-parallel", 1, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("4-way parallel heap merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_4_way_heap_merge_sort_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 4-way heap linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_4_way_heap_merge_sort_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "4-way-heap", 0, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("4-way heap merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_8_way_heap_merge_sort_parallel_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 8-way parallel heap linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_8_way_heap_merge_sort_parallel_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "8-way-heap-parallel", 1, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("8-way parallel heap merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_8_way_heap_merge_sort_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 8-way heap linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_8_way_heap_merge_sort_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "8-way-heap", 0, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("8-way heap merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_16_way_heap_merge_sort_parallel_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 16-way parallel heap linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_16_way_heap_merge_sort_parallel_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "16-way-heap-parallel", 1, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("16-way parallel heap merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_16_way_heap_merge_sort_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 16-way heap linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_16_way_heap_merge_sort_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "16-way-heap", 0, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("16-way heap merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_32_way_heap_merge_sort_parallel_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 32-way parallel heap linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_32_way_heap_merge_sort_parallel_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "32-way-heap-parallel", 1, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("32-way parallel heap merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_32_way_heap_merge_sort_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 32-way heap linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_32_way_heap_merge_sort_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "32-way-heap", 0, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("32-way heap merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}
//noticed speed improvement when cache size is used in the base case
//but heap sort algorithm is not performing well , extermly slow
void test_linked_list_4_way_merge_sort_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 4-way linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_4_way_merge_sort_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "4-way", 0, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("4-way merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_4_way_merge_sort_parallel_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 4-way parallel linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_4_way_merge_sort_parallel_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "4-way-parallel", 1, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("4-way parallel merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_merge_sort_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert){
    
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 2-way linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_merge_sort_q(list4, num_vars, MIN_SORT);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, 1, "2-way", 0, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("2-way merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_merge_sort_parallel_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 2-way parallel linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_merge_sort_parallel_q(list4, num_vars, MIN_SORT);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, 1, "2-way-parallel", 1, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("2-way parallel merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
       
    return;
}

void test_linked_list_8_way_merge_sort_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 8-way linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_8_way_merge_sort_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "8-way", 0, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("8-way merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_8_way_merge_sort_parallel_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 8-way parallel linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_8_way_merge_sort_parallel_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "8-way-parallel", 1, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("8-way parallel merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_16_way_merge_sort_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 16-way linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_16_way_merge_sort_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "16-way", 0, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("16-way merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_16_way_merge_sort_parallel_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 16-way parallel linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_16_way_merge_sort_parallel_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "16-way-parallel", 1, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("16-way parallel merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_32_way_merge_sort_q(char *test_file, int num_vars, linked_list_q *in, bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 32-way linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_32_way_merge_sort_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "32-way", 0, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("32-way merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}

void test_linked_list_32_way_merge_sort_parallel_q(char *test_file, int num_vars, linked_list_q *in , bool maple_assert, long int base_case){
    linked_list_q* list4 = create_linked_list_q();
    
    if(in == NULL){
        list4 = generate_linked_list_from_csv_file(test_file);
        printf("size: %d\n", list4->size);
    }else{
        linked_list_deep_cpy_q(in, list4, num_vars);
    }
    printf("done generating 32-way parallel linked list.     ");
    double  start_time = omp_get_wtime();
    list4 = linked_list_32_way_merge_sort_parallel_q(list4, num_vars, MIN_SORT, base_case);
    double time = omp_get_wtime() - start_time;
    printf("time: %.10f\n", time);
    record_time_to_file("record_time.csv", false, list4->size, base_case, "32-way-parallel", 1, time);
    if(maple_assert){
        char **vars = create_dynamic_str_array(num_vars, "x", "y", "z");
        linked_list_q *temp = create_linked_list_q();
        linked_list_deep_cpy_q(in, temp, num_vars);
        if(in == NULL){
            temp = generate_linked_list_from_csv_file(test_file);
        }
        char *original = print_linked_list_to_string_variable(temp, vars, num_vars);
        linked_list_destroy_q(temp);
        char *list_str_sort = print_linked_list_to_string_variable(list4, vars, num_vars);  
        ASSERT_EQUAL(maple_evaluate_equal(original, list_str_sort), 0);
        parser_test("32-way parallel merge sort test:: ", NULL);
        // // printf("orig:  %s\n", original);
        // // printf("\n\n\n");
        // // printf("sorted: %s\n", list_str_sort);
        free_degrees_variables(vars, num_vars);
        free(original);
        free(list_str_sort);
    }
    
    linked_list_destroy_q(list4);
    return;
}


#ifdef __cplusplus
}
#endif

#endif /* TEST_H */


