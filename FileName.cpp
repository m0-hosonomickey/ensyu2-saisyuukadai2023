#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include<fstream>

using namespace std;
using namespace chrono;


//使用する保存用ベクトルと学習成績の点数の定義
vector<int> selectlog(4);//プレイデータの保存用ベクトル
vector<int>collection(10);//学習データの保存用ベクトル
vector<bool> endcount(6);//エンド回収の保存用ベクトル
int totalscore = 0;//学習成績

//選択肢を表示し入力を受ける関数
void exselect(string choice1, string choice2, string choice3,string choice4,int logvec,int perf) {   
    int ans2 = 0;
    while (true) {//正しい入力がされるまで繰り返す
        
        cout << "1,"<<choice1<<"\n";
        cout << "2,"<<choice2<<"\n";
        cout << "3,"<<choice3<<"\n";
        if (collection[perf-1] == 3) {//所定の問題の達成度が3の時に表示するもの
            cout << "4," << choice4 << "\n";
            cout << "5,ホーム画面に戻る" << "\n";
            cout << "選択してください(1-5):";
            
            cin >> ans2;


            if (ans2 == 1 || ans2 == 2 || ans2 == 3||ans2==4) {//回答をプレイデータを保存するベクトルの所定の場所に格納
                selectlog[logvec] = ans2;
                break;
            }
            if(ans2 == 5) {//「5」が入力されるとプレイデータの保存ベクトルの使用しない領域に「5」が保存される
                break;
                selectlog[3] = 1;
            }
            
        }
        else {
            cout<< "4," << "Q" <<perf<<"をクリアすると選択可能になります" "\n";
            cout << "5,ホーム画面に戻る" << "\n";
            cout << "選択してください(1-3,5):" ;
            int ans2 = 0;
            cin >> ans2;


            if (ans2 == 1 || ans2 == 2 || ans2 == 3) {
                selectlog[logvec] = ans2;
                break;
            }
            if(ans2 == 5) {
                break;
                selectlog[3] = 1;
            }
        }
        cin.clear();//入力を通常状態に戻す
        cin.ignore(numeric_limits<streamsize>::max(), '\n');//不要なデータを破棄
        cout << endl;
        cout << "無効な入力です。選択し直してください" << endl;
         
    }
}


//文字を一文字ずつ表示する関数
void text(string say_text) {
       for (char c : say_text) {//文字を一文字ずつ読み取る
           cout << c;//読み取った内容を表示
           this_thread::sleep_until(system_clock::now() + milliseconds(30));//次の文字を表示するまで30 ms待機　

    }
       cout << endl;
       cout << "<Enterキー>" << endl;
       getchar();//Enterキーが押されるまで待機
}

//キャラクターの名前の表示の後に文字を一文字ずつ表示する関数
void ctext(string character,string csay_text) {
    cout << character << ">>";//キャラクター名>>と表示する
    for (char c : csay_text) {
        cout << c;
        this_thread::sleep_until(system_clock::now() + milliseconds(30));

    }
    cout << endl;
    cout << "<Enterキー>" << endl;
    getchar();
}


//キャラクターの名前，身長，好感度を管理するクラスの定義
class Character {
public:
    string name;//キャラクターの名前
    double height;//キャラクターの身長
    int favorability;//キャラクターの好感度
    
    //キャラクターの情報を入力する関数
    Character(const string& setName, double setHeight, int setFavorability) {//キャラクターの情報を入力
        name = setName;//名前の入力
        height = setHeight;//身長の入力
        favorability = setFavorability;//好感度の入力
        
    }

    void printInfo() const {//    キャラクターの名前，身長，好感度を表示する関数
        cout << "キャラクター名: " << name << endl;
        cout << "身長: " << height << "cm" << endl;
        cout << "好感度: " << favorability << endl;
    }

    void incfav(int amount) {//好感度を上昇させる関数
        if (favorability <= 100-amount) {//好感度+好感度の上昇量が100以下なら好感度を上昇
            cout << name << "好感度:" << favorability << "+" << amount << "\n";//どれだけ好感度を上昇させたか表示
            favorability += amount;//好感度を上昇
        }
        else {
            cout << name << "好感度:" << favorability << "+" << (100-favorability) << "\n";//どれだけ好感度を上昇させたか表示
            favorability = 100;
        }
    }

    void decfav(int amount) {//好感度を低下させる関数
        if (favorability>=amount) {
            cout << name << "好感度:" << favorability << "―" << amount << "\n";
            favorability -= amount;
        }
        else {
            cout << name << "好感度:" << favorability << "―" << favorability << "\n";
            favorability = 0;
        }
    }
};

//キャラクターの情報を管理するベクトルの定義
vector<Character> characters;

//クイズの問題文，2つの選択肢，解説，問題の答え，学習結果の保存場所を管理するクラスの定義
struct quize {
public:
    string quized;//問題文
    string selection1;//選択肢１
    string selection2;//選択肢２
    string commentaly;//解説文
    char qanswer;//答え
    int collect;//学習データの保存場所

    //クイズを表示する関数の定義
    quize(string setquized, string setselection1, string setselection2, string setcommentaly, char setqanswer, int setcollect) {
        quized = setquized;//問題文の入力
        selection1 = setselection1;//選択肢１の入力
        selection2 = setselection2;//選択肢2の入力
        commentaly = setcommentaly;//解説文の入力
        qanswer = setqanswer;//答えの入力
        collect = setcollect;//学習データの保存場所の入力
    }

};


//5の階乗を計算する関数の定義
int factorial(int num) {
    int fac = 1;//何もかけられていないときに１
    for (int i = 1; i <= num; ++i) {//指定された数から1引いた回数だけ5をかける
        fac *= 5;
    }
    return fac;//求めた値を返す
};

//ベクトルのn番目の要素に5^(n―1)をかけた後にベクトルの要素の総和を求める関数の定義（5進数を10進数に変える）
int eprogress() {
    
    int progress = 0;
    int p1 = 0;
    for (auto i = selectlog.begin(); i != selectlog.end(); ++i) {
        progress += *i * factorial(p1);//イテレータでベクトルの要素を取り出して要素の番号に5の階乗をかけての足し算

        ++p1;//p1をひとつずつ増やす
    }
    
    return progress;//求めた値を返す
}


//エンドの作成
void end1() {
    system("cls");//画面の削除
    text("game over\n   end1 永遠にこの会社で…");
    endcount[0] = true;//エンド回収の達成度を管理するベクトルを0から１に変化させる
    characters[0].incfav(1);//1番目のキャラクターの好感度を１上昇させる
    characters[1].incfav(1);
    characters[2].incfav(1);
    cout << "<Enterキー>" << endl;
    getchar();

}

void end2() {
    system("cls");
    text("game over\n   end2 公然わいせつ罪により逮捕");
    endcount[1] = true;
    characters[0].decfav(5);
    characters[1].incfav(10);
    characters[2].decfav(15);
    cout << "<Enterキー>" << endl;
    getchar();
}

void end3() {
    system("cls");
    text("game clear\n   end2 社長最高！ホワイト企業最高！");
    endcount[2] = true;
    characters[0].incfav(5);
    characters[1].decfav(20);
    characters[2].incfav(3);
    cout << "<Enterキー>" << endl;
    getchar();
}
void end4() {
    system("cls");
    text("game clear\n   end4 ブラック企業から脱出成功！");
    endcount[3] = true;
    characters[0].decfav(5);
    characters[1].incfav(0);
    characters[2].decfav(5);
    cout << "<Enterキー>" << endl;
    getchar();
}

void end5() {
    system("cls");
    text("game clear\n   end5 何かを失った気はする…");
    endcount[4] = true;
    characters[0].decfav(5);
    characters[1].incfav(20);
    characters[2].decfav(15);
    cout << "<Enterキー>" << endl;
    getchar();
}

void end6() {
    system("cls");
    text("game clear\n   end6 やっぱりホワイト企業最高！");
    endcount[5] = true;

    characters[0].incfav(5);
    characters[1].decfav(10);
    characters[2].incfav(3);
    cout << "<Enterキー>" << endl;
    getchar();
}

//シーンの作成
void scene1() {
    text("あなたは1000社連続で落ちた末にとてつもないブラック企業である「とにかく重労働株式会社」に入社してしまいました。");

    getchar();

    ctext("木築部長", "今日から君にはここで働いてもらう。この会社は午前中十時間、1度昼休憩を1時間はさんで午後10時間労働してもらったのちに、4時間の就寝時間が与えられる。");



    exselect("一日20時間労働ですか？！", "この世界って1日25時間だっけ？", "とりあえず社長殴らせて下さい", "労働基準法第32条より8時間を超える労働はさせてはいけません！", 0, 4);

}

void scene2() {
    ctext("木築部長", "何を驚いている。みんなやってるんだ。ちなみに逃げられないようにこの部屋は内からでは開けられないようになってる。ちなみにカギは俺と社長しか持ってない。");
    getchar();
    exselect("とりあえず部長を攻撃し、カギを奪う", "「ここで一生働かせてください！」", "全裸になって踊りだす", "「労働基準法第5条。使用者は、暴行、脅迫、監禁その他精神又は身体の自由を不当に拘束する手段によつて、労働者の意思に反して労働を強制してはならない。その内容はこれに反するものだと思いますよ（にやり）」", 1, 5);
    
}

void scene3() {
    text("俺は腕力には自身がある。ハンドボール投げは51ｍだった。こんなおっさん一人くらいぶっ飛ばせるぜ！");
    getchar();
    ctext("あなた", "あんたがカギ持ってるってわざわざ教えてくれてありがとうございまーす！短い間お世話になりました！おらぁぁぁぁぁぁ！");
    text("俺は勢いよく部長にとびかかった。");
    this_thread::sleep_until(system_clock::now() + seconds(2));
    text("ガシッ\n");
    text("部長は軽く受け止めると俺を投げ飛ばした。");
    ctext("木築部長", "君のように俺を倒そうとするやつはたくさんいたよ。元空手の世界チャンピョンだとか、元ボクシングの宇宙チャンピョンだとか。だが、その誰もが今は懸命に働いてくれている。なぜだかわかるか？");
    ctext("あなた", "な、なぜでしょうか？");
    ctext("木築部長", "私に勝てないと悟ってしまったからだよ。ちなみに私のハンドボール投げは70mだ！");
    text("ハンドボール投げ70mだと…？！　　　　　完全に心が折れてしまった。こんな怪物に勝てるわけがない。");
    text("あきらめて一日20時間労働に耐えるしかない…");
    end1();
}

void scene4() {
    ctext("木築部長", "君ぃ計算速いねぇ。気に入った！君は絶対手放さん！");
    getchar();
    end1();
}

void scene5() {
    ctext("木築部長", "お前社長に向かってなんてことをなんてことを！今から社長室に行くぞ！");
    getchar();
    text("手を強く引かれ社長室に向かう");
}

void scene6() {
    ctext("木築部長", "そんなにやる気があるやつは初めてだ！嘘でもそう言ってくれてうれしい！お前は絶対手放さん！");
    end1();
}

void scene7() {
    ctext("あなた", "アッソレ　アッソレ　アッソレソレソレソレ");
    getchar();
    text("よくわかんないけどこんな変態のことは直ぐに解雇してくれるだろう！恥なんて捨てて自由の身に戻るんだ！");
    this_thread::sleep_until(system_clock::now() + seconds(2));
    ctext("美人秘書", "キャーーー！変態よーーー！");
    text("遠くからサイレンの音が聞こえた…");

    end2();
}

void scene8() {
    ctext("木築部長", "な、なんだと？！なに言ってるんだ貴様！そんな法律存在しない！");
    getchar();
    ctext("あなた", "ありますよ。部長の勉強不足では？(笑)");
    ctext("木築部長", "俺が法律にくわしくないからって調子に乗りあがって！こうなったら社長に頼るしかない！");

    text("手を強く引かれ社長室に向かう");
}

void scene9() {
    system("cls");
    cout << "～社長室～" << endl;
    getchar();
    ctext("社長", "木築君。彼はだれかね？");
    ctext("木築部長", "きょ、今日新たに入った新人です。あまりにも生意気言ってたんで社長にしめてもらおうと思って…");
    text("部長がかなりおびえている。どうやらとても強い人のようだ");
    ctext("社長", "君、私の方針に何か不満があるのかね？あったとしても君はすでに一生ここで従順に働くという契約書にサインしてしまっているからもう逃げられないけどね（にやり）");
    exselect("社長を攻撃  攻撃力:" + to_string(totalscore), "それは間違いです！社長！", "とりあえず全裸で腹踊り", "労働基準法第14条。一定の事業の完了に必要な期間を定めるものの他は三年を超える期間について締結してはならない！", 2, 5);
}

void scene10() {
    text("もうよくわかんないけどやるしかない！うおおおおおお");
    getchar();
    if (totalscore == 30) {

        ctext("社長", "ぐはっ。この私が一発でやられるとは");
        text("なんと社長のHPは30だった。");
        ctext("木築部長", "あの宇宙一強い社長が一発で？！やったぁ…泣");
        ctext("社員たち", "よっしゃーーーーー！ついに解放された―ーー！");
        text("社員たちはとても喜び俺を度上げし始めた。部長もとても喜んでる。あぁ最高の気分だ！");

        this_thread::sleep_until(system_clock::now() + seconds(2));

        cout << "～数年後～" << endl;
        text("俺はなんとあれからそのままの勢いで社長になった。");
        text("それからというものこの会社はとてもホワイトな企業に変わった。前は死んだ目で働いていたボクシング宇宙チャンピョンの人もとても楽しそうに働いている。");
        text("暴力で解決してしまったのは良くなかったが、まぁいっか！");
        end3();
    }
    else {
        this_thread::sleep_until(system_clock::now() + seconds(2));
        text("ガシッ");
        ctext("社長", "ふんっ。この私がそんな貧弱なパンチでやられるとでも？");
        text("終わった。よく考えればこんな最強の男に勝てるわけなかった。");
        end1();
    }
}

void scene11() {
    ctext("社長", "何が違うのか説明してくれないかな？（圧力）");
    getchar();
    if (totalscore >= 25) {
        text("くっ、怖いけどここで引き下がったら永遠とここに居続けなければならない。やるしかない！");
        ctext("あなた", "何もかも全部間違ってる！こんなの会社じゃねぇ！");
        ctext("社長", "なに？！まさか私の圧力に負けずに反抗してくるとは…");
        ctext("あなた", "別に社長のやっていることが違法かどうか裁判を起こしてもいいんですよ？");
        ctext("社長", "1000社も落ちるような馬鹿だと思って見くびっていたが君はなかなかにやる男なようだ。");
        text("本当はしっかりと俺のことを知っていたようだ");
        ctext("社長", "次はもっといい会社に入れよ");

        end4();

    }
    else {
        ctext("あなた", "なっ、なにも違わないです（泣）");

        end1();
        text("もっと勉強しましょう");
    }
}

void scene12() {
    ctext("あなた", "アッソレ　アッソレ　アッソレソレソレソレ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        text("よくわかんないけどこんな変態のことは直ぐに解雇してくれるだろう！恥なんて捨てて自由の身に戻るんだ！");
        this_thread::sleep_until(system_clock::now() + seconds(2));
        ctext("美人秘書", "キャーーー！変態よーーー！");
        text("遠くからサイレンの音が聞こえた…");

        end2();
}

void scene13() {
    ctext("あなた", "アッソレ　アッソレ　アッソレソレソレソレ");
    getchar();
    text("よくわかんないけどこんな変態のことは直ぐに解雇してくれるだろう！恥なんて捨てて自由の身に戻るんだ！");
    this_thread::sleep_until(system_clock::now() + seconds(2));
    ctext("美人秘書", "キャーーー！変態よーーー！");

    if (collection[9] < 3) {
        text("遠くからサイレンの音が聞こえた…");

        end2();
    }
    else {
        ctext("木築部長", "すぐに警察に電話します！");
        ctext("あなた", "本当にいいんですか？");
        ctext("木築部長", "ど、どういう意味だ？");
        ctext("あなた", "秘書さんあなたは今17歳ですよね？");
        ctext("美人秘書", "な、なぜそれを？！");
        ctext("あなた", "申し訳ありませんが調べさせてもらいました。");
        ctext("あなた", "労働基準法第61条！満18歳未満の子供を午後十時から午前五時までの間において使用してはならない!");
        text("言い忘れていたが今は午前3時である。");
        text("社長は突然立ち上がると拍手しだした。");
        ctext("社長", "君には恐れ入ったよ本当に。私の完敗だ。訴えるなり好きにしろ。まさかそこまで法律に詳しいとは。");

        text("その後社長は辞任し、次の社長は木築部長部長となった");
        text("しかし木築部長は本当はホワイト企業にあこがれており、会社は一気にホワイトになった");

        end6();
    }
}

void scene14() {
    ctext("社長", "君には恐れ入ったよ本当に。私の完敗だ。訴えるなり好きにしろ。まさかそこまで法律に詳しいとは。");

    text("その後社長は辞任し、次の社長は木築部長部長となった");
    text("しかし木築部長は本当はホワイト企業にあこがれており、会社は一気にホワイトになった");

    end6();

}

void scene15() {
    ctext("あなた", "アッソレ　アッソレ　アッソレソレソレソレ");
    getchar();
    text("よくわかんないけどこんな変態のことは直ぐに解雇してくれるだろう！恥なんて捨てて自由の身に戻るんだ！");
    this_thread::sleep_until(system_clock::now() + seconds(2));
    ctext("美人秘書", "キャーーー！変態よーーー！");
    ctext("社長", "なんて美しい肉体なんだ！");
    ctext("木築部長", "は、はい？");
    ctext("社長", "君の肉体気に入ったよ。君、今夜うちの家に泊まりに来ないかい？");
    ctext("あなた", "は、はい");
    text("思わずそう答えてしまった。");
    text("俺はその晩社長の家に泊まることになった。");
    text("その後どうなったかはあまり話したくない…");
    text("しかし社長に気に入られたおかげでとても良い環境で働けるようになった。");
    end5();
    cout << "Q10の達成度をあげると…";
}

//ストーリーの進行を行う関数を定義
void blackgame(){
    while (true) {

        cout << "続きから進行しますか？(y/n)" << endl;
        char tuduki;
        cin >> tuduki;
        if (tuduki == 'y') {
            break;
        }
        if (tuduki == 'n') {
            for (int i = 0;i < 3;++i) {
                selectlog[i] = 0;
            }

            break;

        }
        
    }
    system("cls");

    int gprogress = eprogress();//ゲームの進行状況をを算出する

    if (gprogress == 0) {//gprogressが0の時に表示される
        scene1();

        gprogress = eprogress();//選択肢の後では進行状況を書き直す
    }

    gprogress = eprogress();

    if (gprogress == 1) {
        scene2();

        gprogress = eprogress();

    }


    if (gprogress == 6) {
        scene3();

    }

    if (gprogress == 7) {
        scene6();
    }

    if (gprogress == 16) {
        scene7();

    }


    if (gprogress == 2) {
        scene4();

    }



    if (gprogress == 3) {
        scene5();

    }

    if (gprogress == 4 || gprogress == 21) {
        scene8();

    }

    if (gprogress == 3 || gprogress == 4 || gprogress == 21) {
        scene9();

        gprogress = eprogress();

    }
    if (gprogress == 28 || gprogress == 29 || gprogress == 46) {
        scene10();
    }

    if (gprogress == 53 || gprogress == 54 || gprogress == 71) {
        scene11();

    }
    if (gprogress == 78) {
        if (totalscore < 20) {
            scene12();
        }
        if (totalscore >= 20) {
            scene15();
        }
    }

    if (gprogress == 79 || gprogress == 96) {
        scene13();

    }
    if (gprogress == 103 || gprogress == 104 || gprogress == 121) {
        scene14();

    }
}

//労働基準法の学習を行う関数の定義
void rquize() {
    quize quizzes[10] = {//10問のクイズを配列にする
        quize("Q1:使用者は、暴行、脅迫、監禁その他精神又は身体の自由を不当に拘束する手段によつて、労働者の意思に反して労働を強制してはならない。","1：OK","2：NO","当然いけません(第5条)",'1',collection[0]),
        quize("Q2:使用者は、労働契約不履行ついて違約金を定めることができるが、損害賠償額を予定する契約をしてはならない。","1：OK","2：NO","違約金を定めることも禁止されています。(第16条)",'2',collection[1]),
        quize("Q3:賃金は、毎月一回以上、一定の期日を定めて支払わなければならない","1：OK","2：NO","賃金は、毎月一回以上、一定の期日を定めて支払わなければならない。ただし、臨時に支払われる賃金、賞与その他これに準ずるもので厚生労働省令で定める賃金(第八十九条において「臨時の賃金等」という。)については、この限りでない。(第24条)",'1',collection[2]),
        quize("Q4:使用者は、一週間の各日については、労働者に、休憩時間を除き一日について十時間を超えて、労働させてはならない。","1：OK","2：NO","八時間を超えて労働させてはいけません（第32条）",'2',collection[3]),
        quize("Q5:労働契約は、期間の定めのないものを除き、一定の事業の完了に必要な期間を定めるものの他は二年を超える期間について締結してはならない。","1：OK","2：NO","二年ではなく三年です。(第14条)",'2',collection[4]),
        quize("Q6:使用者は、労働者に対して、毎週少くとも一回の休日を与えなくても、四週間を通じ四日以上の休日を与えていれば問題ない","1：OK","2：NO","毎週少なくとも一回の休日を与えなればならないという規定は、四週間を通じ四日以上の休日を与える使用者については適用しない。（第35条）",'1',collection[5]),
        quize("Q7:使用者の責に帰すべき事由による休業の場合においては、使用者は、休業期間中当該労働者に、その平均賃金の50%以上の手当を支払わなければならない。","1：OK","2：NO","60％以上である。（第26条）",'2',collection[6]),
        quize("Q8:使用者は、労働時間が六時間を超える場合においては少くとも一時間の休憩時間を労働時間の途中に与えなければならない。","1：OK","2：NO","六時間を超える場合は少なくとも45分以上、八時間を超える場合は少なくとも一時間以上休憩を与える必要があります。（第34条）",'2',collection[7]),
        quize("Q9:使用者は、その雇入れの日から起算して六箇月間継続勤務し全労働日の九割以上出勤した労働者に対して、継続し、又は分割した十労働日の有給休暇を与えなければならない。","1：OK","2：NO","九割ではなく八割です。（第39条）",'2',collection[8]),
        quize("Q10:交代制によって使用する16歳の男性を午後十時から午前五時までの間において使用するのは問題ない。","1：OK","2：NO","使用者は、満十八才に満たない者を午後十時から午前五時までの間において使用してはならない。ただし、交替制によつて使用する満十六才以上の男性については、この限りでない。(第61条)",'1',collection[9]),

    };

    //ランダムに問題を五問選出
    vector<int> selectquestion = { 0,1,2,3,4,5,6,7,8,9 };

    random_device engine;
    mt19937 a(engine());
    uniform_int_distribution<> dis(0, 9);

    shuffle(selectquestion.begin(), selectquestion.end(), a);//selectquestionベクトルを乱数でランダムに並び替える

    auto itr = selectquestion.begin();//初めの要素のイテレータ

    int conum = 0;//今回の成績を計算するのに使用する

    //一問ずつ問題を表示
    for (int i = 0;i < 5;++i) {
        system("cls");

        //ランダムに並べ替えられたselectquestionベクトルの要素をひとつづつ取り出す
        cout << quizzes[*(itr + i)].quized << endl;//問題文の表示
        cout << quizzes[*(itr + i)].selection1 << endl;//選択肢１の表示
        cout << quizzes[*(itr + i)].selection2 << endl;//選択肢２の表示

        //達成度の表示
        cout << "達成度：";
        for (int point = 0;point < collection[*(itr + i)];++point) {//達成度の数だけ○を表示
            cout << "〇";
        }

        for (int point = 0;point < 3 - collection[*(itr + i)];++point) {//3ー達成度の数だけ●を表示
            cout << "●";
        }
        cout << endl;

        cout << "選択してください(1-2):" ;


        char userans;//ユーザーの入力
        cin >> userans;//ユーザーの入力を入れる


        if (userans == quizzes[*(itr + i)].qanswer) {//答えが一致
            cout << "正解です！" << endl;//正解と表示
            cout << "解説:" << quizzes[*(itr + i)].commentaly << endl;//解説文の表示
            cout << "<Enterキー>";
            getchar();//Enterキーが押されるまで待機
            getchar();//上の待機状態が入力の際のエンターキーで終わってしまうため，もう一つ追加
            ++conum;//成績を１増やす
            if (collection[*(itr + i)] < 3) {//達成度が３未満なら達成度を１プラス
                collection[*(itr + i)] += 1;
            }
        }


        if (userans != quizzes[*(itr + i)].qanswer) {//答えが不一致



            cout << "不正解です" << endl;
            cout << "解説:" << quizzes[selectquestion[i]].commentaly << endl;
            cout << "<Enterキー>";
            getchar();
            getchar();
            if (collection[*(itr + i)] > 0) {//達成度が0より大きければ達成度を１マイナス
                collection[*(itr + i)] += -1;
            }


        }

    }

    ofstream outfile("seitouritsu.txt");//学習データの保存
    for (int i = 0;i < 10;++i) {//一行ずつ学習データのベクトルの要素を保存
        outfile << collection[i] << endl;

    }
    outfile.close();
    cout << "5問中" << conum << "問正解" << endl;//今回の成績を表示
    cout << "<Enterキー>";
    getchar();
}

//保存を行う関数の定義
void gamelog() {
    system("cls");
    cout << "保存しますか？(y/n)" << endl;
    string log;
    cin >> log;
    if (log == "y") {
        ofstream outfile("sinndo.txt");//ゲームの進行状態をファイルに保存
        for (int i = 0;i < 12;++i) {//12かい繰り返す
            if (i < 3) {//初めの3つはプレイデータの保存
                outfile << selectlog[i] << endl;
            }
            if (i >= 3&&i<9) {//4個めから9個めまではエンド回収の達成度の保存
                outfile << endcount[i - 3] << endl;
            }
            if (i >= 9) {//11個めから13個めから好感度の保存
                outfile << characters[i-9].favorability << endl;
            }

        }

        outfile.close();//ファイルを閉じる
        text("保存しました");
        getchar();
    }
}




int main() {
    //キャラクターの情報を登録
    characters.push_back(Character("木築部長", 165.0, 50));
    characters.push_back(Character("木菱社長", 170.5, 50));
    characters.push_back(Character("美人秘書", 158.2, 50));

    //学習データの取り込み
    ifstream infile1("seitouritsu.txt");

    int x1;
    int t1 = 0;
    if (infile1) {
        while (infile1 >> x1) {//ファイルの上から順に学習データを保存するベクトルに格納していく

            collection[t1] = x1;
            ++t1;

        }
        infile1.close();
    }

    /*for (int i = 0;i < 10;++i) {   //達成度をマックスにしたいときに使用してください
            collection[i]=3;
        }*/

    ifstream infile2("sinndo.txt");//プレイデータ，エンド回収の達成度，好感度の読み取り
    int x2;
    int t2 = 0;
    if (infile2) {
        while (infile2 >> x2) {
            if (t2 < 3) {//上から3個めまでを順にプレイデータを保存するベクトルに格納
                selectlog[t2] = x2;
            }
            if (t2 >= 3 && t2 < 9) {//上から4個めから9個めをエンド回収の達成度を保存するベクトルに格納
                endcount[t2 - 3] = x2;
            }
            if (t2 >= 9 && t2 < 12) {//上から10個めから12個めをキャラクター1から3の好感度にする
                characters[t2 - 9].favorability = x2;
            }
            ++t2;
        }
        infile2.close();
    }
    int choice = 0;//セレクト画面での選択肢の入力を入れる変数

    while (true) {

        totalscore = 0;//学習成績を一度0に戻す
       


        for (int i = 0;i < 10;++i) {//達成度を全て合計し，学習成績を算出
            totalscore += collection[i];
        }

        //セレクト画面の表示
        system("cls");
        cout << "ブラック企業から逃げろ！" << endl;
        cout << "1. ゲーム情報を表示" << endl;
        cout << "2. ゲームスタート" << endl;
        cout << "3. 保存" << endl;
        cout << "4. データの初期化" << endl;
        cout << "5. ゲームの終了" << endl;
        cout << "選択してください(1-5): ";
        char choice;
        cin >> choice;


        //ゲーム情報の表示
        if (choice == '1') {//セレクト画面で「1」を選択
            system("cls");
            
            for (const auto& character : characters) {//キャラクターの情報表示
                character.printInfo();
                cout << endl;
            }
            for (int i = 0;i < 6;++i) {//エンド回収の達成度表示
                cout << "end"<<i+1<<":";
                if (endcount[i] == 1) {
                    cout << "達成\n";
                }
                if (endcount[i] == 0) {
                    cout << "未達成\n";
                }
            }
            
            cout << "学習成績:" << totalscore << "/30"<<endl;//学習進度の表示
            cout << endl;
            for (int i = 0;i < 10;++i) {
                cout << "Q" << i + 1 ;
                cout << "達成度：";


                for (int point = 0;point < collection[i];++point) {
                    cout << "〇";
                }

                for (int point = 0;point < 3 - collection[i];++point) {
                    cout << " ●";
                }
                cout << endl;
                
                
            }
            cout << "Enterキーを押して下さい" << endl;

            
            getchar();
            getchar();
        }
        else if (choice == '2') {//セレクト画面で「2」を選択

            system("cls");

            cout << "1,ストーリーの進行\n" << "2,労働基準法の学習\n" << endl;//ストーリーの進行と労働基準法の学習を選択肢表示
            char gameselect;//上記の選択肢に対する入力を入れる変数
            cout << "どちらをを進行しますか？ (1-2): ";
            cin >> gameselect;//入力

            if (gameselect == '1') {//「1」を選択

                system("cls");
                blackgame();//ストーリーの進行を行う関数を起動

                continue;//ストーリーの進行が終わったらセレクト画面に戻るためループの最後へ移動

            }

            if (gameselect == '2') {//「2」を選択
                system("cls");

                rquize();//労働基準法の学習を行う関数を起動

            }
        }

        else if (choice == '3') {//セレクト画面で「3」を選択

            gamelog();//保存する関数の起動

        }

        else if (choice == '4') {//セレクト画面で「4」を選択
            system("cls");
            cout << "初期化しますか？(y/n)" << endl;
            string reset;//上記の質問に対する答えを入れる変数
            cin >> reset;//答えの入力
            if (reset == "y") {//上記の質問に「ｙ」と入力

                //プレイデータ，エンド回収の達成度，好感度の初期化
                ofstream outfile1("sinndo.txt");
                for (int i = 0;i < 12;++i) {//プレイデータとして読み込まれる3個めまでをすべて0に
                    if (i < 3) {
                        outfile1 << 0 << endl;
                    }
                    if (i >= 3&&i<9) {//エンド回収の達成度として読み込まれる4個めから9個めをすべて0に
                        outfile1 << 0 << endl;
                    }
                    if (i >= 9) {//好感度として読み込まれる10個めから12個めまでをすべて50に
                        outfile1 << 50 << endl;
                    }

                }
                outfile1.close();

                //学習データの初期化
                ofstream outfile2("seitouritsu.txt");
                for (int i = 0;i < 10;++i) {//学習データとして読み込まれる部分をすべて0に
                    outfile2 << 0 << endl;

                }
                outfile2.close();
                text("初期化しました");
                text("プログラムを終了します");
                break;//プログラムを終了させる
            }
        }

        else if (choice == '5'){//セレクト画面で「5」を選択
            system("cls");
            cout << "終了しますか？(y/n)" << endl;
            char finish;//上記の質問に対する答えをいれる変数
            cin >> finish;//答えを入力
            if (finish == 'y') {//「ｙ」と入力
                text("終了します");
                getchar();
                break;//プログラムを終了させる
            }
        }
    }
}

    



