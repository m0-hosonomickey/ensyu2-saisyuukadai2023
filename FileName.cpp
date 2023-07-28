#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include<fstream>

using namespace std;
using namespace chrono;


//�g�p����ۑ��p�x�N�g���Ɗw�K���т̓_���̒�`
vector<int> selectlog(4);
vector<int>collection(10);
vector<bool> endcount(6);
int totalscore = 0;

//�I������\�������͂��󂯂�֐�
void exselect(string choice1, string choice2, string choice3,string choice4,int logvec,int perf) {   
    int ans2 = 0;
    while (true) {
        
        cout << "1,"<<choice1<<"\n";
        cout << "2,"<<choice2<<"\n";
        cout << "3,"<<choice3<<"\n";
        if (collection[perf-1] == 3) {//����̖��̒B���x��3�̎��ɕ\���������
            cout << "4," << choice4 << "\n";
            cout << "5,�z�[����ʂɖ߂�" << "\n";
            cout << "�I�����Ă�������(1-5):";
            
            cin >> ans2;


            if (ans2 == 1 || ans2 == 2 || ans2 == 3||ans2==4) {//�񓚂��v���C�f�[�^��ۑ�����x�N�g���̏���̏ꏊ�Ɋi�[
                selectlog[logvec] = ans2;
                break;
            }
            if(ans2 == 5) {//�u5�v�����͂����ƃv���C�f�[�^�̕ۑ��x�N�g���̎g�p���Ȃ��̈�Ɂu5�v���ۑ������
                break;
                selectlog[3] = 1;
            }
            
        }
        else {
            cout<< "4," << "Q" <<perf<<"���N���A����ƑI���\�ɂȂ�܂�" "\n";
            cout << "5,�z�[����ʂɖ߂�" << "\n";
            cout << "�I�����Ă�������(1-3,5):" ;
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
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        cout << "�����ȓ��͂ł��B�I���������Ă�������" << endl;
         
    }
}


//�������ꕶ�����\������֐�
void text(string say_text) {
       for (char c : say_text) {
           cout << c;
           this_thread::sleep_until(system_clock::now() + milliseconds(30));//���̕�����\������܂�30 ms�ҋ@�@

    }
       cout << endl;
       cout << "<Enter�L�[>" << endl;
       getchar();//Enter�L�[���������܂őҋ@
}

//�L�����N�^�[�̖��O�̕\���̌�ɕ������ꕶ�����\������֐�
void ctext(string character,string csay_text) {
    cout << character << ">>";
    for (char c : csay_text) {
        cout << c;
        this_thread::sleep_until(system_clock::now() + milliseconds(30));

    }
    cout << endl;
    cout << "<Enter�L�[>" << endl;
    getchar();
}


//�L�����N�^�[�̖��O�C�g���C�D���x���Ǘ�����N���X�̒�`
class Character {
public:
    string name;
    double height;
    int favorability;
    

public:
    Character(const string& setName, double setHeight, int setFavorability) {
        name = setName;
        height = setHeight;
        favorability = setFavorability;
        
    }

    void printInfo() const {//    �L�����N�^�[�̖��O�C�g���C�D���x��\������֐�
        cout << "�L�����N�^�[��: " << name << endl;
        cout << "�g��: " << height << "cm" << endl;
        cout << "�D���x: " << favorability << endl;
    }

    void incfav(int amount) {//�D���x���㏸������֐�
        if (favorability <= 100-amount) {
            cout << name << "�D���x:" << favorability << "+" << amount << "\n";
            favorability += amount;
        }
        else {
            cout << name << "�D���x:" << favorability << "+" << 0 << "\n";
        }
    }

    void decfav(int amount) {//�D���x��ቺ������֐�
        if (favorability>=amount) {
            cout << name << "�D���x:" << favorability << "�\" << amount << "\n";
            favorability -= amount;
        }
    }
};

//�L�����N�^�[�̏����Ǘ�����x�N�g���̒�`
vector<Character> characters;

//�N�C�Y�̖�蕶�C2�̑I�����C����C���̓����C�w�K���ʂ̕ۑ��ꏊ���Ǘ�����N���X�̒�`
struct quize {
public:
    string quized;
    string selection1;
    string selection2;
    string commentaly;
    char qanswer;
    int collect;

    //�N�C�Y��\������֐��̒�`
    quize(string setquized, string setselection1, string setselection2, string setcommentaly, char setqanswer, int setcollect) {
        quized = setquized;
        selection1 = setselection1;
        selection2 = setselection2;
        commentaly = setcommentaly;
        qanswer = setqanswer;
        collect = setcollect;
    }

};


//5�̊K����v�Z����֐��̒�`
int factorial(int num) {
    int fac = 1;
    for (int i = 1; i <= num; ++i) {
        fac *= 5;
    }
    return fac;
};

//�x�N�g����n�Ԗڂ̗v�f��5^(n�\1)����������Ƀx�N�g���̗v�f�̑��a�����߂�֐��̒�`
int eprogress() {
    
    int progress = 0;
    int p1 = 0;
    for (auto i = selectlog.begin(); i != selectlog.end(); ++i) {
        progress += *i * factorial(p1);//�C�e���[�^�Ńx�N�g���̗v�f�����o���đ����Z

        ++p1;
    }
    
    return progress;
}


//�G���h�̍쐬
void end1() {
    system("cls");
    text("game over\n   end1 �i���ɂ��̉�ЂŁc");
    endcount[0] = true;
    characters[0].incfav(1);
    characters[1].incfav(1);
    characters[2].incfav(1);
    cout << "<Enter�L�[>" << endl;
    getchar();

}

void end2() {
    system("cls");
    text("game over\n   end2 ���R�킢���߂ɂ��ߕ�");
    endcount[1] = true;
    characters[0].decfav(5);
    characters[1].incfav(10);
    characters[2].decfav(15);
    cout << "<Enter�L�[>" << endl;
    getchar();
}

void end3() {
    system("cls");
    text("game clear\n   end2 �В��ō��I�z���C�g��ƍō��I");
    endcount[2] = true;
    characters[0].incfav(5);
    characters[1].decfav(20);
    characters[2].incfav(3);
    cout << "<Enter�L�[>" << endl;
    getchar();
}
void end4() {
    system("cls");
    text("game clear\n   end4 �u���b�N��Ƃ���E�o�����I");
    endcount[3] = true;
    characters[0].decfav(5);
    characters[1].incfav(0);
    characters[2].decfav(5);
    cout << "<Enter�L�[>" << endl;
    getchar();
}

void end5() {
    system("cls");
    text("game clear\n   end5 �������������C�͂���c");
    endcount[4] = true;
    characters[0].decfav(5);
    characters[1].incfav(20);
    characters[2].decfav(15);
    cout << "<Enter�L�[>" << endl;
    getchar();
}

void end6() {
    system("cls");
    text("game clear\n   end6 ����ς�z���C�g��ƍō��I");
    endcount[5] = true;

    characters[0].incfav(5);
    characters[1].decfav(10);
    characters[2].incfav(3);
    cout << "<Enter�L�[>" << endl;
    getchar();
}

//�V�[���̍쐬
void scene1() {
    text("���Ȃ���1000�ИA���ŗ��������ɂƂĂ��Ȃ��u���b�N��Ƃł���u�Ƃɂ����d�J��������Ёv�ɓ��Ђ��Ă��܂��܂����B");

    getchar();

    ctext("�ؒz����", "��������N�ɂ͂����œ����Ă��炤�B���̉�Ђ͌ߑO���\���ԁA1�x���x�e��1���Ԃ͂���Ōߌ�10���ԘJ�����Ă�������̂��ɁA4���Ԃ̏A�Q���Ԃ��^������B");



    exselect("���20���ԘJ���ł����H�I", "���̐��E����1��25���Ԃ������H", "�Ƃ肠�����В����点�ĉ�����", "�J����@��32�����8���Ԃ𒴂���J���͂����Ă͂����܂���I", 0, 4);

}

void scene2() {
    ctext("�ؒz����", "���������Ă���B�݂�Ȃ���Ă�񂾁B���Ȃ݂ɓ������Ȃ��悤�ɂ��̕����͓�����ł͊J�����Ȃ��悤�ɂȂ��Ă�B���Ȃ݂ɃJ�M�͉��ƎВ����������ĂȂ��B");
    getchar();
    exselect("�Ƃ肠�����������U�����A�J�M��D��", "�u�����ňꐶ�������Ă��������I�v", "�S���ɂȂ��ėx�肾��", "�u�J����@��5���B�g�p�҂́A�\�s�A�����A�ċւ��̑����_���͐g�̂̎��R��s���ɍS�������i�ɂ�āA�J���҂̈ӎv�ɔ����ĘJ�����������Ă͂Ȃ�Ȃ��B���̓��e�͂���ɔ�������̂��Ǝv���܂���i�ɂ��j�v", 1, 5);
    
}

void scene3() {
    text("���͘r�͂ɂ͎��g������B�n���h�{�[��������51���������B����Ȃ��������l���炢�Ԃ���΂��邺�I");
    getchar();
    ctext("���Ȃ�", "���񂽂��J�M�����Ă���Ă킴�킴�����Ă���Ă��肪�Ƃ��������܁[���I�Z���Ԃ����b�ɂȂ�܂����I���炟�����������I");
    text("���͐����悭�����ɂƂт��������B");
    this_thread::sleep_until(system_clock::now() + seconds(2));
    text("�K�V�b\n");
    text("�����͌y���󂯎~�߂�Ɖ��𓊂���΂����B");
    ctext("�ؒz����", "�N�̂悤�ɉ���|�����Ƃ����͂������񂢂���B�����̐��E�`�����s�������Ƃ��A���{�N�V���O�̉F���`�����s�������Ƃ��B�����A���̒N�������͌����ɓ����Ă���Ă���B�Ȃ������킩�邩�H");
    ctext("���Ȃ�", "�ȁA�Ȃ��ł��傤���H");
    ctext("�ؒz����", "���ɏ��ĂȂ��ƌ���Ă��܂������炾��B���Ȃ݂Ɏ��̃n���h�{�[��������70m���I");
    text("�n���h�{�[������70m���Ɓc�H�I�@�@�@�@�@���S�ɐS���܂�Ă��܂����B����ȉ����ɏ��Ă�킯���Ȃ��B");
    text("������߂Ĉ��20���ԘJ���ɑς��邵���Ȃ��c");
    end1();
}

void scene4() {
    ctext("�ؒz����", "�N���v�Z�����˂��B�C�ɓ������I�N�͐�Ύ������I");
    getchar();
    end1();
}

void scene5() {
    ctext("�ؒz����", "���O�В��Ɍ������ĂȂ�Ă��Ƃ��Ȃ�Ă��Ƃ��I������В����ɍs�����I");
    getchar();
    text("�������������В����Ɍ�����");
}

void scene6() {
    ctext("�ؒz����", "����Ȃɂ��C�������͏��߂Ă��I�R�ł����������Ă���Ă��ꂵ���I���O�͐�Ύ������I");
    end1();
}

void scene7() {
    ctext("���Ȃ�", "�A�b�\���@�A�b�\���@�A�b�\���\���\���\��");
    getchar();
    text("�悭�킩��Ȃ����ǂ���ȕϑԂ̂��Ƃ͒����ɉ��ق��Ă���邾�낤�I�p�Ȃ�Ď̂ĂĎ��R�̐g�ɖ߂�񂾁I");
    this_thread::sleep_until(system_clock::now() + seconds(2));
    ctext("���l�鏑", "�L���[�[�[�I�ϑԂ�[�[�[�I");
    text("��������T�C�����̉������������c");

    end2();
}

void scene8() {
    ctext("�ؒz����", "�ȁA�Ȃ񂾂ƁH�I�ȂɌ����Ă�񂾋M�l�I����Ȗ@�����݂��Ȃ��I");
    getchar();
    ctext("���Ȃ�", "����܂���B�����̕׋��s���ł́H(��)");
    ctext("�ؒz����", "�����@���ɂ��킵���Ȃ�������Ē��q�ɏ�肠�����āI�����Ȃ�����В��ɗ��邵���Ȃ��I");

    text("�������������В����Ɍ�����");
}

void scene9() {
    system("cls");
    cout << "�`�В����`" << endl;
    getchar();
    ctext("�В�", "�ؒz�N�B�ނ͂��ꂩ�ˁH");
    ctext("�ؒz����", "����A�����V���ɓ������V�l�ł��B���܂�ɂ����ӋC�����Ă���ŎВ��ɂ��߂Ă��炨���Ǝv���āc");
    text("���������Ȃ肨�т��Ă���B�ǂ����ƂĂ������l�̂悤��");
    ctext("�В�", "�N�A���̕��j�ɉ����s��������̂��ˁH�������Ƃ��Ă��N�͂��łɈꐶ�����ŏ]���ɓ����Ƃ����_�񏑂ɃT�C�����Ă��܂��Ă��邩������������Ȃ����ǂˁi�ɂ��j");
    exselect("�В����U��  �U����:" + to_string(totalscore), "����͊ԈႢ�ł��I�В��I", "�Ƃ肠�����S���ŕ��x��", "�J����@��14���B���̎��Ƃ̊����ɕK�v�Ȋ��Ԃ��߂���̂̑��͎O�N�𒴂�����Ԃɂ��Ē������Ă͂Ȃ�Ȃ��I", 2, 5);
}

void scene10() {
    text("�����悭�킩��Ȃ����ǂ�邵���Ȃ��I��������������");
    getchar();
    if (totalscore == 30) {

        ctext("�В�", "���͂��B���̎����ꔭ�ł����Ƃ�");
        text("�Ȃ�ƎВ���HP��30�������B");
        ctext("�ؒz����", "���̉F���ꋭ���В����ꔭ�ŁH�I��������c��");
        ctext("�Ј�����", "�������[�[�[�[�[�I���ɉ�����ꂽ�\�[�[�I");
        text("�Ј������͂ƂĂ���щ���x�グ���n�߂��B�������ƂĂ����ł�B�����ō��̋C�����I");

        this_thread::sleep_until(system_clock::now() + seconds(2));

        cout << "�`���N��`" << endl;
        text("���͂Ȃ�Ƃ��ꂩ�炻�̂܂܂̐����ŎВ��ɂȂ����B");
        text("���ꂩ��Ƃ������̂��̉�Ђ͂ƂĂ��z���C�g�Ȋ�Ƃɕς�����B�O�͎��񂾖ڂœ����Ă����{�N�V���O�F���`�����s�����̐l���ƂĂ��y�������ɓ����Ă���B");
        text("�\�͂ŉ������Ă��܂����̂͗ǂ��Ȃ��������A�܂��������I");
        end3();
    }
    else {
        this_thread::sleep_until(system_clock::now() + seconds(2));
        text("�K�V�b");
        ctext("�В�", "�ӂ���B���̎�������ȕn��ȃp���`�ł����Ƃł��H");
        text("�I������B�悭�l����΂���ȍŋ��̒j�ɏ��Ă�킯�Ȃ������B");
        end1();
    }
}

void scene11() {
    ctext("�В�", "�����Ⴄ�̂��������Ă���Ȃ����ȁH�i���́j");
    getchar();
    if (totalscore >= 25) {
        text("�����A�|�����ǂ����ň�������������i���Ƃ����ɋ������Ȃ���΂Ȃ�Ȃ��B��邵���Ȃ��I");
        ctext("���Ȃ�", "���������S���Ԉ���Ă�I����Ȃ̉�Ђ���˂��I");
        ctext("�В�", "�ȂɁH�I�܂������̈��͂ɕ������ɔ��R���Ă���Ƃ́c");
        ctext("���Ȃ�", "�ʂɎВ��̂���Ă��邱�Ƃ���@���ǂ����ٔ����N�����Ă�������ł���H");
        ctext("�В�", "1000�Ђ�������悤�Ȕn�����Ǝv���Č����т��Ă������N�͂Ȃ��Ȃ��ɂ��j�Ȃ悤���B");
        text("�{���͂�������Ɖ��̂��Ƃ�m���Ă����悤��");
        ctext("�В�", "���͂����Ƃ�����Ђɓ����");

        end4();

    }
    else {
        ctext("���Ȃ�", "�Ȃ��A�Ȃɂ����Ȃ��ł��i���j");

        end1();
        text("�����ƕ׋����܂��傤");
    }
}

void scene12() {
    ctext("���Ȃ�", "�A�b�\���@�A�b�\���@�A�b�\���\���\���\��");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        text("�悭�킩��Ȃ����ǂ���ȕϑԂ̂��Ƃ͒����ɉ��ق��Ă���邾�낤�I�p�Ȃ�Ď̂ĂĎ��R�̐g�ɖ߂�񂾁I");
        this_thread::sleep_until(system_clock::now() + seconds(2));
        ctext("���l�鏑", "�L���[�[�[�I�ϑԂ�[�[�[�I");
        text("��������T�C�����̉������������c");

        end2();
}

void scene13() {
    ctext("���Ȃ�", "�A�b�\���@�A�b�\���@�A�b�\���\���\���\��");
    getchar();
    text("�悭�킩��Ȃ����ǂ���ȕϑԂ̂��Ƃ͒����ɉ��ق��Ă���邾�낤�I�p�Ȃ�Ď̂ĂĎ��R�̐g�ɖ߂�񂾁I");
    this_thread::sleep_until(system_clock::now() + seconds(2));
    ctext("���l�鏑", "�L���[�[�[�I�ϑԂ�[�[�[�I");

    if (collection[9] < 3) {
        text("��������T�C�����̉������������c");

        end2();
    }
    else {
        ctext("�ؒz����", "�����Ɍx�@�ɓd�b���܂��I");
        ctext("���Ȃ�", "�{���ɂ�����ł����H");
        ctext("�ؒz����", "�ǁA�ǂ������Ӗ����H");
        ctext("���Ȃ�", "�鏑���񂠂Ȃ��͍�17�΂ł���ˁH");
        ctext("���l�鏑", "�ȁA�Ȃ�������H�I");
        ctext("���Ȃ�", "�\���󂠂�܂��񂪒��ׂ����Ă��炢�܂����B");
        ctext("���Ȃ�", "�J����@��61���I��18�Ζ����̎q�����ߌ�\������ߑO�܎��܂ł̊Ԃɂ����Ďg�p���Ă͂Ȃ�Ȃ�!");
        text("�����Y��Ă��������͌ߑO3���ł���B");
        text("�В��͓ˑR�����オ��Ɣ��肵�������B");
        ctext("�В�", "�N�ɂ͋����������{���ɁB���̊��s���B�i����Ȃ�D���ɂ���B�܂��������܂Ŗ@���ɏڂ����Ƃ́B");

        text("���̌�В��͎��C���A���̎В��͖ؒz���������ƂȂ���");
        text("�������ؒz�����͖{���̓z���C�g��Ƃɂ�������Ă���A��Ђ͈�C�Ƀz���C�g�ɂȂ���");

        end6();
    }
}

void scene14() {
    ctext("�В�", "�N�ɂ͋����������{���ɁB���̊��s���B�i����Ȃ�D���ɂ���B�܂��������܂Ŗ@���ɏڂ����Ƃ́B");

    text("���̌�В��͎��C���A���̎В��͖ؒz���������ƂȂ���");
    text("�������ؒz�����͖{���̓z���C�g��Ƃɂ�������Ă���A��Ђ͈�C�Ƀz���C�g�ɂȂ���");

    end6();

}

void scene15() {
    ctext("���Ȃ�", "�A�b�\���@�A�b�\���@�A�b�\���\���\���\��");
    getchar();
    text("�悭�킩��Ȃ����ǂ���ȕϑԂ̂��Ƃ͒����ɉ��ق��Ă���邾�낤�I�p�Ȃ�Ď̂ĂĎ��R�̐g�ɖ߂�񂾁I");
    this_thread::sleep_until(system_clock::now() + seconds(2));
    ctext("���l�鏑", "�L���[�[�[�I�ϑԂ�[�[�[�I");
    ctext("�В�", "�Ȃ�Ĕ��������̂Ȃ񂾁I");
    ctext("�ؒz����", "�́A�͂��H");
    ctext("�В�", "�N�̓��̋C�ɓ�������B�N�A���邤���̉Ƃɔ��܂�ɗ��Ȃ������H");
    ctext("���Ȃ�", "�́A�͂�");
    text("�v�킸���������Ă��܂����B");
    text("���͂��̔ӎВ��̉Ƃɔ��܂邱�ƂɂȂ����B");
    text("���̌�ǂ��Ȃ������͂��܂�b�������Ȃ��c");
    text("�������В��ɋC�ɓ���ꂽ�������łƂĂ��ǂ����œ�����悤�ɂȂ����B");
    end5();
    cout << "Q10�̒B���x��������Ɓc";
}

//�X�g�[���[�̐i�s���s���֐����`
void blackgame(){
    while (true) {

        cout << "��������i�s���܂����H(y/n)" << endl;
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

    int gprogress = eprogress();

    if (gprogress == 0) {//gprogress��0�̎��ɕ\�������
        scene1();

        gprogress = eprogress();
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

//�N�C�Y
void rquize() {
    quize quizzes[10] = {
        quize("Q1:�g�p�҂́A�\�s�A�����A�ċւ��̑����_���͐g�̂̎��R��s���ɍS�������i�ɂ�āA�J���҂̈ӎv�ɔ����ĘJ�����������Ă͂Ȃ�Ȃ��B","1�FOK","2�FNO","���R�����܂���(��5��)",'1',collection[0]),
        quize("Q2:�g�p�҂́A�J���_��s���s���Ĉ������߂邱�Ƃ��ł��邪�A���Q�����z��\�肷��_������Ă͂Ȃ�Ȃ��B","1�FOK","2�FNO","�������߂邱�Ƃ��֎~����Ă��܂��B(��16��)",'2',collection[1]),
        quize("Q3:�����́A�������ȏ�A���̊������߂Ďx����Ȃ���΂Ȃ�Ȃ�","1�FOK","2�FNO","�����́A�������ȏ�A���̊������߂Ďx����Ȃ���΂Ȃ�Ȃ��B�������A�Վ��Ɏx����������A�ܗ^���̑�����ɏ�������̂Ō����J���ȗ߂Œ�߂����(�攪�\����ɂ����āu�Վ��̒������v�Ƃ����B)�ɂ��ẮA���̌���łȂ��B(��24��)",'1',collection[2]),
        quize("Q4:�g�p�҂́A��T�Ԃ̊e���ɂ��ẮA�J���҂ɁA�x�e���Ԃ���������ɂ��ď\���Ԃ𒴂��āA�J�������Ă͂Ȃ�Ȃ��B","1�FOK","2�FNO","�����Ԃ𒴂��ĘJ�������Ă͂����܂���i��32���j",'2',collection[3]),
        quize("Q5:�J���_��́A���Ԃ̒�߂̂Ȃ����̂������A���̎��Ƃ̊����ɕK�v�Ȋ��Ԃ��߂���̂̑��͓�N�𒴂�����Ԃɂ��Ē������Ă͂Ȃ�Ȃ��B","1�FOK","2�FNO","��N�ł͂Ȃ��O�N�ł��B(��14��)",'2',collection[4]),
        quize("Q6:�g�p�҂́A�J���҂ɑ΂��āA���T�����Ƃ����̋x����^���Ȃ��Ă��A�l�T�Ԃ�ʂ��l���ȏ�̋x����^���Ă���Ζ��Ȃ�","1�FOK","2�FNO","���T���Ȃ��Ƃ����̋x����^���Ȃ�΂Ȃ�Ȃ��Ƃ����K��́A�l�T�Ԃ�ʂ��l���ȏ�̋x����^����g�p�҂ɂ��Ă͓K�p���Ȃ��B�i��35���j",'1',collection[5]),
        quize("Q7:�g�p�҂̐ӂɋA���ׂ����R�ɂ��x�Ƃ̏ꍇ�ɂ����ẮA�g�p�҂́A�x�Ɗ��Ԓ����Y�J���҂ɁA���̕��ϒ�����50%�ȏ�̎蓖���x����Ȃ���΂Ȃ�Ȃ��B","1�FOK","2�FNO","60���ȏ�ł���B�i��26���j",'2',collection[6]),
        quize("Q8:�g�p�҂́A�J�����Ԃ��Z���Ԃ𒴂���ꍇ�ɂ����Ă͏����Ƃ��ꎞ�Ԃ̋x�e���Ԃ�J�����Ԃ̓r���ɗ^���Ȃ���΂Ȃ�Ȃ��B","1�FOK","2�FNO","�Z���Ԃ𒴂���ꍇ�͏��Ȃ��Ƃ�45���ȏ�A�����Ԃ𒴂���ꍇ�͏��Ȃ��Ƃ��ꎞ�Ԉȏ�x�e��^����K�v������܂��B�i��34���j",'2',collection[7]),
        quize("Q9:�g�p�҂́A���̌ٓ���̓�����N�Z���ĘZ�ӌ��Ԍp���Ζ����S�J�����̋㊄�ȏ�o�΂����J���҂ɑ΂��āA�p�����A���͕��������\�J�����̗L���x�ɂ�^���Ȃ���΂Ȃ�Ȃ��B","1�FOK","2�FNO","�㊄�ł͂Ȃ������ł��B�i��39���j",'2',collection[8]),
        quize("Q10:��㐧�ɂ���Ďg�p����16�΂̒j�����ߌ�\������ߑO�܎��܂ł̊Ԃɂ����Ďg�p����͖̂��Ȃ��B","1�FOK","2�FNO","�g�p�҂́A���\���˂ɖ����Ȃ��҂��ߌ�\������ߑO�܎��܂ł̊Ԃɂ����Ďg�p���Ă͂Ȃ�Ȃ��B�������A��֐��ɂ�Ďg�p���閞�\�Z�ˈȏ�̒j���ɂ��ẮA���̌���łȂ��B(��61��)",'1',collection[9]),

    };

    //�����_���ɖ����ܖ�I�o
    vector<int> selectquestion = { 0,1,2,3,4,5,6,7,8,9 };

    random_device engine;
    mt19937 a(engine());
    uniform_int_distribution<> dis(0, 9);

    shuffle(selectquestion.begin(), selectquestion.end(), a);

    auto itr = selectquestion.begin();

    int conum = 0;//����̐��т��v�Z

    //��₸����\��
    for (int i = 0;i < 5;++i) {
        system("cls");


        cout << quizzes[*(itr + i)].quized << endl;
        cout << quizzes[*(itr + i)].selection1 << endl;
        cout << quizzes[*(itr + i)].selection2 << endl;
        cout << "�B���x�F";


        for (int point = 0;point < collection[*(itr + i)];++point) {
            cout << "�Z";
        }

        for (int point = 0;point < 3 - collection[*(itr + i)];++point) {
            cout << "��";
        }
        cout << endl;

        cout << "�I�����Ă�������(1-2):" ;


        char userans;
        cin >> userans;


        if (userans == quizzes[*(itr + i)].qanswer) {
            cout << "�����ł��I" << endl;
            cout << "���:" << quizzes[*(itr + i)].commentaly << endl;
            cout << "<Enter�L�[>";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ++conum;
            if (collection[*(itr + i)] < 3) {
                collection[*(itr + i)] += 1;
            }
        }


        if (userans != quizzes[*(itr + i)].qanswer) {



            cout << "�s�����ł�" << endl;
            cout << "���:" << quizzes[selectquestion[i]].commentaly << endl;
            cout << "<Enter�L�[>";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (collection[*(itr + i)] > 0) {
                collection[*(itr + i)] += -1;
            }


        }

    }

    ofstream outfile("seitouritsu.txt");//�w�K�f�[�^�̕ۑ�
    for (int i = 0;i < 10;++i) {
        outfile << collection[i] << endl;

    }
    outfile.close();
    cout << "5�⒆" << conum << "�␳��" << endl;
    cout << "<Enter�L�[>";
    getchar();
}

//�ۑ����s���֐��̒�`
void gamelog() {
    system("cls");
    cout << "�ۑ����܂����H(y/n)" << endl;
    string log;
    cin >> log;
    if (log == "y") {
        ofstream outfile("sinndo.txt");
        for (int i = 0;i < 12;++i) {
            if (i < 3) {
                outfile << selectlog[i] << endl;
            }
            if (i >= 3&&i<9) {
                outfile << endcount[i - 3] << endl;
            }
            if (i >= 9) {
                outfile << characters[i-9].favorability << endl;
            }

        }

        outfile.close();
        text("�ۑ����܂���");
        getchar();
    }
}




int main() {
    vector<int> selection;
    
    characters.push_back(Character("�ؒz����", 165.0, 50));
    characters.push_back(Character("�ؕH�В�", 170.5, 50));
    characters.push_back(Character("���l�鏑", 158.2, 50));

    ifstream infile1("seitouritsu.txt");
    int x1;
    int t1 = 0;
    if (infile1) {
        while (infile1 >> x1) {

            collection[t1] = x1;
            ++t1;

        }
        infile1.close();
    }
    ifstream infile2("sinndo.txt");
    int x2;
    int t2 = 0;
    if (infile2) {
        while (infile2 >> x2) {
            if (t2 < 3) {
                selectlog[t2] = x2;
            }
            if (t2 >= 3 && t2 < 9) {
                endcount[t2 - 3] = x2;
            }
            if (t2 >= 9 && t2 < 12) {
                characters[t2 - 9].favorability = x2;
            }
            ++t2;
        }
        infile2.close();
    }
    int choice = 0;

    while (true) {

        totalscore = 0;
       
        for (int i = 0;i < 10;++i) {
            totalscore += collection[i];
        }

        /*for (int i = 0;i < 10;++i) {
            collection[i]=3;
        }*/
        system("cls");
        cout << "�u���b�N��Ƃ��瓦����I" << endl;
        cout << "1. �Q�[������\��" << endl;
        cout << "2. �Q�[���X�^�[�g" << endl;
        cout << "3. �ۑ�" << endl;
        cout << "4. �f�[�^�̏�����" << endl;
        cout << "5. �Q�[���̏I��" << endl;
        cout << "�I�����Ă�������(1-5): ";
        char choice;
        cin >> choice;



        if (choice == '1') {
            system("cls");
            
            for (const auto& character : characters) {
                character.printInfo();
                cout << endl;
            }
            for (int i = 0;i < 6;++i) {
                cout << "end"<<i+1<<":";
                if (endcount[i] == 1) {
                    cout << "�B��\n";
                }
                if (endcount[i] == 0) {
                    cout << "���B��\n";
                }
            }
            
            cout << "�w�K����:" << totalscore << "/30"<<endl;
            cout << endl;
            for (int i = 0;i < 10;++i) {
                cout << "Q" << i + 1 ;
                cout << "�B���x�F";


                for (int point = 0;point < collection[i];++point) {
                    cout << "�Z";
                }

                for (int point = 0;point < 3 - collection[i];++point) {
                    cout << " ��";
                }
                cout << endl;
                
                
            }
            cout << "Enter�L�[�������ĉ�����" << endl;

            
            getchar();
            getchar();
        }
        else if (choice == '2') {

            system("cls");

            cout << "1,�X�g�[���[�̐i�s\n" << "2,�J����@�̊w�K\n" << endl;
            char gameselect;
            cout << "�ǂ������i�s���܂����H (1-2): ";
            cin >> gameselect;

            if (gameselect == '1') {

                system("cls");
                blackgame();

                continue;

            }

            if (gameselect == '2') {
                system("cls");

                rquize();

            }
        }

        else if (choice == '3') {

            gamelog();

        }

        else if (choice == '4') {
            system("cls");
            cout << "���������܂����H(y/n)" << endl;
            string reset;
            cin >> reset;
            if (reset == "y") {
                ofstream outfile1("sinndo.txt");
                for (int i = 0;i < 12;++i) {
                    if (i < 3) {
                        outfile1 << 0 << endl;
                    }
                    if (i >= 3&&i<9) {
                        outfile1 << 0 << endl;
                    }
                    if (i >= 9) {
                        outfile1 << 50 << endl;
                    }

                }
                outfile1.close();
                ofstream outfile2("seitouritsu.txt");
                for (int i = 0;i < 10;++i) {
                    outfile2 << 0 << endl;

                }
                outfile2.close();
                text("���������܂���");
                text("�v���O�������I�����܂�");
                break;
            }
        }

        else if (choice == '5'){
            system("cls");
            cout << "�I�����܂����H(y/n)" << endl;
            char finish;
            cin >> finish;
            if (finish == 'y') {
                text("�I�����܂�");
                getchar();
                break;
            }
        }
    }
}

    



