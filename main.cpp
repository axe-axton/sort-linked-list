#include <iostream>
#include<cstring>
#include<conio.h>
#include<cstdio>

using namespace std;

int i=0;
struct student{
    char* id;
    char* name;
    char subject[10];

    short semester;
    short score;

    student(){id=NULL; name=NULL; semester=0; score=0;};
    student* next;
};

class op_list{
public:
    op_list();

    bool check();
    bool is_ssame(short);
    void sort_data();
    void add();
    void show();


private:
    enum choose{stop,_continue};
    student* _student;//head

};

short input_str(char*& word);

int main()
{
    op_list o;
    char choose;
    while(1){
        o.add();
        o.show();
        cout<<"\nTake another student data? (Y/N)";
        cin>>choose;
        if(choose>90)
            choose-=32;
        if(choose!='Y')
            break;
        cin.clear();
        cin.ignore(255,'\n');
    }
    return 0;
}

op_list::op_list(){
    _student=NULL;
}

bool op_list::check(){
    if(_student!=NULL)
        return true;

    return false;
}

bool op_list::is_ssame(short current){
    student* help=_student;
    while(help!=NULL){
        if(help->score==current)
            return true;
        help=help->next;
    }
    return false;
}

void op_list::sort_data(){

    if(_student==NULL)
        return;

    student* current=_student,*after=NULL,*temp_data=new student;
    short temp;

    while(current!=NULL)
    {
        after=current->next;
        while(after!=NULL){

            if(current->score < after->score){
                temp_data->id=(char*)malloc(100*sizeof(char));
                temp_data->name=(char*)malloc(100*sizeof(char));

                temp=current->score;
                temp_data->semester=current->semester;
                strcpy(temp_data->id,current->id);
                strcpy(temp_data->name,current->name);
                strcpy(temp_data->subject,current->subject);

                current->score=after->score;
                current->semester=after->semester;
                strcpy(current->id,after->id);
                strcpy(current->name,after->name);
                strcpy(current->subject,after->subject);

                after->score=temp;
                after->semester=temp_data->semester;
                strcpy(after->id,temp_data->id);
                strcpy(after->name,temp_data->name);
                strcpy(after->subject,temp_data->subject);

                delete(temp_data->id);
                delete(temp_data->name);
            }

            after=after->next;
        }
        current=current->next;
    }
    delete after;
    delete temp_data;
}

void op_list::add(){

    char* failure="data cant be empty try again";
    if(!check()){
        student* help=new student;
        try{
            cout<<"Get the ID:";
            if(input_str(help->id))
                throw failure;
            cout<<"Get the Name:";
            if(input_str(help->name))
                throw failure;
            cout<<"Get the Semester:";
            cin>>help->semester;
            cout<<"Get the Subject:";
            cin>>help->subject;

            if(cin.fail()){
                cin.clear();
                throw failure;
            }

            cout<<"Get the Score:";
            cin>>help->score;
        }
        catch(const char*){
            cout<<failure<<endl;
            return;
        }

        _student=help;
        _student->next=NULL;
    }
    else{
        student* help=_student;
        student* add_student=new student;

        try{
            cout<<"Get the ID:";
            if(input_str(add_student->id))
                throw failure;
            cout<<"Get the Name:";
            if(input_str(add_student->name))
                throw failure;

            cout<<"Get the Semester:";
            cin>>add_student->semester;
            cout<<"Get the Subject:";
            cin>>add_student->subject;
            if(cin.fail()){
                    cin.clear();
                throw failure;
            }

            cout<<"Get the Score:";
            cin>>add_student->score;

            if(is_ssame(add_student->score)){
                cout<<"same data try again\n";
                return;
            }
        }
        catch(const char*){
            cout<<failure<<endl;
            return;
        }

        while(help->next!=NULL)
            help=help->next;
        help->next=add_student;
        add_student->next=NULL;
        sort_data();
    }
}

void op_list::show(){
    student* help=_student;
    while(help!=NULL){

        cout<<"("<<help->id<<","<<help->name<<","<<help->semester<<","<<help->subject<<","<<help->score<<") --> ";
        help=help->next;
    }
}


short input_str(char*& word){
    char c;
    int len=2;
    word=new char[len];

    int i=0;

    while(std::cin.get(c))
    {
        if(c=='\n')
            break;

        if(i==len)
        {
            char temp[len];
            strcpy(temp,word);

            len+=4;
            delete word;
            word=new char[len];

            strcpy(word,temp);
            delete temp;
        }

        word[i]=c;

        i++;
    }
    //i++;
    word[i]='\0';
    if(word[0]=='\0')
        return 1;

    return 0;
}



