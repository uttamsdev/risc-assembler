#include <bits/stdc++.h>
#include <sstream>
#include <string>

using namespace std;


void BinarytoHex(string binnum,ofstream &out)
{
    char hexa[1000];
    string app="";
    int temp;
    long int i=0,j=0;

    while(binnum[i]){
        binnum[i] = binnum[i] -48;
        ++i;
    }
    --i;
    while(i-2>=0){
        temp =  binnum[i-3] *8 + binnum[i-2] *4 +  binnum[i-1] *2 + binnum[i] ;
        if(temp > 9)
            hexa[j++] = temp + 55;
        else
            hexa[j++] = temp + 48;
        i=i-4;
    }
    if(i ==1)
        hexa[j] = binnum[i-1] *2 + binnum[i] + 48 ;
    else if(i==0)
        hexa[j] =  binnum[i] + 48 ;
    else
        --j;

    while(j>=0){
        app += hexa[j--];
    }
    out<<app<<endl;
}

///Convert decimalToBinary
string  decimalToBinary_four(int n)
{
    std::string binary = std::bitset<4>(n).to_string();

    return binary;
}

string  decimalToBinary_ten(int n)
{
    std::string binary = std::bitset<10>(n).to_string();

    return binary;
}

int main()
{

    string binary,bin;
    ifstream input;
    input.open("input.txt");
    ofstream output;
    output.open("output_binary.txt");
    ofstream output2;
    output2.open("output_hexa.txt");

    string op, rs, rt, rd, j,cons ;
    string instruction,fil;

    string opn, rsn, rtn, rdn ;

    string R[2][13];
    int temp=1;

    R[0][0] = "ADD";
    R[1][0] = "0000";

    R[0][1] = "SUB";
    R[1][1] = "0001";

    R[0][2] = "SRL";
    R[1][2] = "0010";

    R[0][3] = "SLL";
    R[1][3] = "0011";

    R[0][4] = "AND";
    R[1][4] = "0100";

    R[0][5] = "OR";
    R[1][5] = "0101";

    R[0][6] = "XOR";
    R[1][6] = "0110";

    R[0][7] = "ADDI";
    R[1][7] = "0111";

    R[0][8] = "LW";
    R[1][8] = "1000";

    R[0][9] = "SW";
    R[1][9] = "1001";

    R[0][10] = "BEQ";
    R[1][10] = "1010";

    R[0][11] = "BNE";
    R[1][11] = "1011";

    R[0][12] = "J";
    R[1][12] = "1100";


    string registers[2][8];


    registers[0][0] = "$zero";
    registers[1][0] = "000";

    registers[0][1] = "$t0";
    registers[1][1] = "001";

    registers[0][2] = "$t1";
    registers[1][2] = "010";

    registers[0][3] = "$t2";
    registers[1][3] = "011";

    registers[0][4] = "$t3";
    registers[1][4] = "100";

    registers[0][5] = "$s0";
    registers[1][5] = "101";

    registers[0][6] = "$s1";
    registers[1][6] = "110";

    registers[0][7] = "$s2";
    registers[1][7] = "111";

    int i;

    while(input>>instruction)
    {

        for( i=0; i<13; i++)
        {
            if(instruction == R[0][i])
            {
                op = R[1][i];
                break;
            }
        }

        if(i==13)
        {
            cout<<"Instruction not found!"<<endl;
        }


        if(op=="0000"||op=="0001"||op=="0100"||op=="0101"||op=="0110") ///ADD+SUB+AND+OR+XOR
        {
            string rs,rd,rt;

            input>>rd>>rs>>rt;

            rd.erase(rd.begin()+rd.length()-1, rd.end());
            rs.erase(rs.begin()+rs.length()-1, rs.end());

            int count = 0;
            for(int i=0; i<8; i++)
            {
                if(count==3)
                {
                    break;
                }
                if(rd==registers[0][i])
                {
                    rdn = registers[1][i];

                    if(rdn=="000")
                    {
                        cout<<"Zero can't be used"<<endl;
                        temp=0;

                        break;
                    }
                    count++;
                }
                if(rs==registers[0][i])
                {
                    rsn = registers[1][i];
                    count++;
                }
                if(rt==registers[0][i])
                {
                    rtn = registers[1][i];
                    count++;
                }
            }

            if(temp)
            {
                string shbin ="0";

                binary = op+rdn+rsn+rtn+shbin;
                BinarytoHex(binary,output2);

                output<<op<<rdn<<rsn<<rtn<<shbin<<endl;
            }
            else
            {
                output<<endl;
            }
            temp=1;
        }

        else if(op=="0111")      ///ADDI
        {
            string shstr;
            stringstream shstrtemp;
            int sh;
            string shbin;
            input>>rd>>rs>>sh;
            if(sh>15)
            {
                cout<<"Invalid Address"<<endl;
                temp=0;
            }
            if(sh<0)
            {
                cout<<"Invalid Address"<<endl;
                temp=0;
            }
            else
            {
                shbin=decimalToBinary_four(sh);
            }
            rd.erase(rd.begin()+rd.length()-1, rd.end());
            rs.erase(rs.begin()+rs.length()-1, rs.end());
            int count = 0;

            for(int i=0; i<8; i++)
            {
                if(count==2)
                {
                    break;
                }
                if(rd==registers[0][i])
                {
                    rdn = registers[1][i];
                    if((rdn=="000" && op=="0111"))
                    {
                        cout<<"Zero can't be used"<<endl;
                        temp=0;
                        break;
                    }
                    count++;
                }

                if(rs==registers[0][i])
                {
                    rsn = registers[1][i];
                    count++;
                }
            }

            j ="000";

            if(temp)
            {
                binary = op+rdn+rsn+shbin;
                output<<op<<rdn<<rsn<<shbin<<endl;

                BinarytoHex(binary,output2);
            }
            else
            {
                output<<endl;
            }

            temp=1;
        }



        else if(op=="0010" || op=="0011")      ///SRL+SLL
        {
            string shstr;
            stringstream shstrtemp;
            int sh;
            string shbin;
            input>>rd>>rs>>sh;
            if(sh>1)
            {
                cout<<"Invalid Address"<<endl;
                temp=0;
            }
            if(sh<0)
            {
                cout<<"Invalid Address"<<endl;
                temp=0;
            }
            else
            {
                shbin=decimalToBinary_four(sh);
            }
            rd.erase(rd.begin()+rd.length()-1, rd.end());
            rs.erase(rs.begin()+rs.length()-1, rs.end());
            int count = 0;

            for(int i=0; i<8; i++)
            {
                if(count==2)
                {
                    break;
                }
                if(rd==registers[0][i])
                {
                    rdn = registers[1][i];
                    if((rdn=="000" && op=="0010") || (rdn=="000" && op=="0011"))
                    {
                        cout<<"Zero can't be used"<<endl;
                        temp=0;
                        break;
                    }
                    count++;
                }

                if(rs==registers[0][i])
                {
                    rsn = registers[1][i];
                    count++;
                }
            }


            if(temp)
            {
                binary = op+rdn+rsn+shbin;
                output<<op<<rdn<<rsn<<shbin<<endl;

                BinarytoHex(binary,output2);
            }
            else
            {
                output<<endl;
            }

            temp=1;
        }


        else if(op=="1010" || op =="1011")      ///BEQ+BNE
        {
            string shstr;
            stringstream shstrtemp;
            int sh;
            string shbin;
            input>>rd>>rs>>sh;

            if( sh<0)
            {
                cout<<"Invalid Address"<<endl;
                temp=0;
            }
            if(sh>15)
            {
                cout<<"Invalid Address"<<endl;
                temp=0;
            }

            else
            {
                shbin=decimalToBinary_four(sh);

            }
            rd.erase(rd.begin()+rd.length()-1, rd.end());
            rs.erase(rs.begin()+rs.length()-1, rs.end());


            int count = 0;

            for(int i=0; i<8; i++)
            {
                if(count==2)
                {
                    break;
                }
                if(rd==registers[0][i])
                {
                    rdn = registers[1][i];
                    if((rdn=="000" && op=="1010") || (rdn =="000" && op == "1011"))
                    {
                        cout<<"Zero can't be used"<<endl;
                        temp=0;
                        break;
                    }
                    count++;
                }

                if(rs==registers[0][i])
                {
                    rsn = registers[1][i];
                    count++;
                }
            }


            j ="000";

            if(temp)
            {

                binary = op+rdn+rsn+shbin;
                output <<op<<rdn<<rsn<<shbin<<endl;

                BinarytoHex(binary,output2);
            }
            else
            {
                output<<endl;
            }

            temp=1;
        }

        else if(op=="1000"||op=="1001")       ///LW+SW
        {
            registers[0][0] = "$zero";

            string rdin, rsin;
            string immediate, source;
            input>>rdin>>source;
            for(int i=0; i<source.length(); i++)
            {
                if(source[i]=='$')
                {
                    rsin = rsin+source[i]+source[i+1]+source[i+2];
                    break;
                }
            }
            for(int i=0; i<source.length(); i++)
            {
                if(source[i]=='(')
                    break;
                immediate = immediate+source[i];
            }
            rdin.erase(rdin.begin()+rdin.length()-1, rdin.end());
            int value = atoi(immediate.c_str());
                //value*=2;

            int count = 0;

            for(int i=0; i<8; i++)
            {
                if(count==3)
                {
                    break;
                }
                if(rdin==registers[0][i])
                {
                    rdn = registers[1][i];
                    if(rdn=="000")
                    {
                        cout<<"Zero can't be used"<<endl;
                        temp=0;
                        break;
                    }
                    count++;
                }
                if(rsin==registers[0][i])
                {
                    rsn = registers[1][i];
                    count++;
                }

            }

            if(value>=0 && value <16)
            {
                string shbin=decimalToBinary_four(value);

                immediate =shbin;

                if(temp)
                {
                    output<<op<<rdn<<rsn<<immediate<<endl;
                    binary =op+rdn+rsn+immediate;
                    BinarytoHex(binary,output2);
                }
                else
                {
                    output<<endl;
                }

            }
            else
            {
                cout<<"Invalid Offset!"<<endl;
                output<<endl;
            }

            temp=1;
            registers[0][0] = "$zero";

        }

        else if(op=="1100")       ///j
        {
            string shstr;
            stringstream shstrtemp;
            int sh,temp=1;
            string shbin;


            input>>sh;
            if(sh<0)
            {
                cout<<"Invalid address"<<endl;
                temp=0;

            }
            if(sh>1024)
            {
                cout<<"Invalid address"<<endl;
                temp=0;

            }
            else
            {
                shbin=decimalToBinary_ten(sh);
            }
            rd.erase(rd.begin()+rd.length()-1, rd.end());
            rs.erase(rs.begin()+rs.length()-1, rs.end());

            if(temp)
            {
                output<<op<<shbin<< endl;

                binary=op+shbin;

                BinarytoHex(binary,output2);
            }
            else
            {
                output<<endl;
            }

            temp=1;
        }
    }

    cout<<"Successfully converted to binary as well as hexadecimal"<<endl;

    return 0;
}
