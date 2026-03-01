#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Foods * create0();   //完成
void search_inf(struct Foods* headf);   //完成+附加功能
struct Foods* delete(struct Foods* headf,char * food_name);     //完成
void edit(struct Foods* headf);             //完成
void tips(struct Foods* headf);
void save_data(struct Foods* headf);
struct Foods * load_data();
void free_list(struct Foods* headf);
struct Foods * append_list(struct Foods * headf, struct Foods * new_headf);





struct Foods
    {
        char name[500];                           //食物名字
        float food_volume;                        //食物体积
        float safe_temperature;                     //食物保存温度
        int type;                                 //食物种类:0蔬菜 1肉类 2水果
        struct Foods* next;           
    };
struct Foods food;


    

    float fridge_volume = 100.0;    // 冰箱总容积
    float fridge_used = 0.0;        // 已使用容积
    float fridge_temperature = 0.0;     //冰箱默认温度

int main()  
{   
    char food_name[500];
    int choice;
    struct Foods * foods_list = NULL;
    
    printf("正在在四维空间创建冰箱酱 喵～\n");
    printf("在四维空间创建冰箱酱成功 喵～\n");
    printf("正在加载上次的数据喵~:\n");
    foods_list = load_data();
    if (foods_list != NULL)
    {
        printf("加载成功喵~ 冰箱酱记忆恢复了！\n");
    }
    else
    {
        printf("没有历史数据喵~ 从空冰箱开始！\n");
    }   
    while(1) 
    {
        printf("\n请输入操作模式(0为拿出，1为输入，2为查询，3为修改，4为建议,5为退出): ");
        scanf("%d",&choice);
        getchar(); 
        
        switch(choice)
        {
            case(0): // 拿出食物
                if (foods_list == NULL)
                {
                    printf("食物链表为空！喵～\n");
                } 
                else 
                {
                    printf("请输入要删除的食物名称 喵～：");
                    scanf("%s", food_name);
                    foods_list=delete(foods_list, food_name);
                    save_data(foods_list);
                }
                break;
        
            case(1): // 输入食物
            {
                struct Foods * new_list=create0();
                foods_list=append_list(foods_list,new_list);
                save_data(foods_list);
                break;
            }
                

            case(2): // 查询
            {
                search_inf(foods_list);
                break;
            }
                

            case(3):    //编辑
            {
                edit(foods_list);
                save_data(foods_list);
                break;
            }
                
                
            case(5): // 退出系统
            {
                printf("正在退出冰箱管理系统喵～\n");
                save_data(foods_list);
                free_list(foods_list);
                goto exit; 
            }
                

            case(4): //建议
            {
                tips(foods_list);
                break;
            }
                

            default:
            {
                printf("无效操作，请重新输入喵～\n");
                break;
            }
                
        }   
    }
    
exit:
    ;   
    system("pause");
    return 0;
}


struct Foods * create0()                 //创建食物链表
{
    struct Foods *headf, *pf=NULL,*qf=NULL;
    headf=NULL;
    while(1)
    {
        pf=((struct Foods*)malloc(sizeof (struct Foods)));
        if(pf == NULL)          // 内存检查
        {
            printf("内存分配失败喵~!\n");
            return headf;
        }
        printf("请输入食物名称喵~(输入end结束):");
        scanf("%s",pf->name);

        if(strcmp(pf->name,"end")==0)
        {
            free(pf); 
            break; 
            
        }
        while (1)
        {
            printf("请输入食物体积喵~:");
            scanf("%f",&pf->food_volume);
            if (pf->food_volume+fridge_used>fridge_volume)
            {
                printf("冰箱酱装不下了，冰箱酱最多保存容量为100的东西啊啊啊/(ㄒoㄒ)/~~");
                printf("剩余容积: %.2f 喵~: ", fridge_volume - fridge_used);
                free(pf);
                return headf;
            }
            else 
            {
                break;
            }
        }
            
        while(1)
        {
            printf("请输入保存温度(冰箱酱最多保存-20摄氏度~10摄氏度)喵~：");
            scanf("%f", &pf->safe_temperature);
            if (pf->safe_temperature<-20||pf->safe_temperature>10)
            {
                printf("食物要坏掉了,抱歉啊...冰箱酱最多保存-20摄氏度~10摄氏度啊啊啊");
                free(pf);
                return headf;
            }
            else 
            {
                break;
            }
            
        }
        
        
        printf("请输入食物种类喵~(0蔬菜 1肉类 2水果)：");
        scanf("%d", &pf->type);
        pf->next=NULL;

        if (headf==NULL)
        {
            headf=pf;
            qf=pf;
        }
        else
        {
            qf->next=pf;
            qf=pf;
            
        }
        fridge_used+=pf->food_volume;
        printf("添加成功！已使用：%f/%f喵~\n",fridge_used,fridge_volume);
        printf("\n");
    }
    return headf;
}


struct Foods* delete(struct Foods* headf,char * food_name)      //删除（拿出）食物
{
    if (headf==NULL||food_name==NULL) 
    {
        printf("无效！空的！你确定吗，喵~\n");
        return headf;
    }
    struct Foods *pf=headf,*qf=NULL;
    while (pf!=NULL&& strcmp(pf->name,food_name)!=0)
    {
        qf=pf;  
        pf=pf->next;
    }
    if (pf==NULL)
    {
        printf("冰箱不知道哦＞︿＜\n");
        return headf;
    }
    
    fridge_used-=pf->food_volume;
    if (qf==NULL)
    {
        headf=pf->next;
    }
    else
    {
        qf->next=pf->next;
    }
    
    free(pf);
    printf("冰箱已经消灭这个食物了捏~\n");      //已经删除食物
    return headf;
}

void search_inf(struct Foods* headf)
{
    if (headf==NULL)
    {
        printf("冰箱酱里空空如也~喵~\n");
        return;
    }
    printf("冰箱酱状态如下：\n");
    printf("容积:%f/%f\n",fridge_used,fridge_volume);
    printf("温度:%f\n",fridge_temperature);

    int type_search;                 //查询
    printf("请选择查询模式\n(1=按照种类；2=按照名称；3=按照数量)喵~\n");
    scanf("%d",&type_search);
    
    switch(type_search)
    {
        case(1):            //种类
        {
            int kind;
            printf("请输入食物种类喵~:\n");
            printf("0. 蔬菜\n");
            printf("1. 肉类\n");
            printf("2. 水果\n");
            printf("请输入种类编号(0-2): ");
            scanf("%d", &kind);

            if(kind<0||kind>2) 
            {
                printf("种类编号错误喵~!\n");
                return;
            }
            struct Foods *pf=headf;
            int count=0;
            float volume=0.0;           //查询的体积

            while (pf!=NULL)
            {
                if (pf->type==kind)
                {
                    count++;
                    volume+=pf->food_volume;
                    printf("名字：%s 数量：%d 温度：%f 体积: %f\n",pf->name,count,pf->safe_temperature,pf->food_volume);
                    if (fridge_temperature>=pf->safe_temperature)
                    {
                        printf("目前温度适合喵~");

                    }
                    else
                    {
                        printf("目前温度不大适合喵~");
                    }

                }
                pf=pf->next;
            }
                
            

            if (count==0) printf("没有了哦~(┬┬﹏┬┬)");
            else printf("该类食物共有%d个，总体积为%f喵~\n", count, volume);
            break;
        }
        case(2):                //名称
        {
            char food_title[500];
            printf("输入名字喵~:");
            scanf("%s",&food_title);
            struct Foods *pf=headf;
            int found=0;
            while(pf!=NULL)
            {
                if (strcmp(pf->name,food_title)==0) 
                {
                    found=1;
                    printf("Nice.找到辣~");
                    printf("食物名字: %s\n", pf->name);
                    printf("食物体积: %f\n", pf->food_volume);
                    printf("食物保存温度: %f°C\n", pf->safe_temperature);
                    printf("食物种类: ");
                    if (pf->type==0)
                    {
                        printf("介个是蔬菜! 喵~");
                    }
                    else if (pf->type==1) printf("介个是肉类 喵~");
                    else if (pf->type==2) printf("介个是水果 喵~"); 
                    break;
                }
                pf=pf->next;
            }
            if (found==0)
            {
                printf("Noooo!没找到%s啊啊啊\n",food_title);
            }
            break;
        }
        case(3):                //数量
        {
            struct Foods* pf = headf;
            int total = 0;              //总数
            float all_volume = 0.0;    
            while(pf != NULL) 
            {
                total++;
                all_volume += pf->food_volume;
                pf = pf->next;
            }     
            printf("食物总数: %d 个\n", total);
            printf("总占用体积: %f/%f\n", all_volume, fridge_volume);
            printf("剩余容积: %f\n", fridge_volume - all_volume);
            break;
        }
        default:
        {
            printf("查询方式输入不正确捏~\n");
            break;
        }
    }
}

void edit(struct Foods* headf)
{
    if (headf==NULL)
    {
        printf("冰箱酱里空空如也~喵~\n");
        return;
    }
    char food_name[500];
    printf("请输入要修改的食物名字喵（￣︶￣）↗ ：");
    scanf("%s",&food_name);

    struct Foods *pf=headf;
    while (pf!=NULL&& strcmp(pf->name,food_name)!=0)
    {
          
        pf=pf->next;
    }
    if (pf==NULL)
    {
        printf("冰箱不知道哦＞︿＜\n");
        return ;
    }
    printf("找到了喵~\n");
    printf("当前信息如下:\n");
    printf("名字: %s\n", pf->name);
    printf("体积: %.2f\n", pf->food_volume);
    printf("温度: %f°C\n", pf->safe_temperature);
    printf("种类: ");
    switch(pf->type)
    {
        case(0): printf("介个是蔬菜喵~\n"); break;
        case(1): printf("介个是肉类喵~\n"); break;
        case(2): printf("介个是水果喵~\n"); break;

    }
    int option;
    printf("选择要修改的地方 喵~:\n");
    printf("1. 修改食物的体积\n");
    printf("2. 修改保存的温度\n");
    printf("3. 修改食物的种类\n");
    printf("4. 取消修改操作\n");
    scanf("%d",&option);
    switch(option)
    {
        case(1):
        {
            float old_volume=pf->food_volume;  //保存原来的体积
            float new_volume;                       //设定新的体积
            printf("现在TA的体积是:%f",old_volume);
            printf("输入新的体积喵:");
            scanf("%f",&new_volume);
            float change=0.0;
            change=new_volume-old_volume;
            if(fridge_used+change>fridge_volume)
            {
                printf("冰箱酱装不下了喵~！(╯°□°）╯︵ ┻━┻\n");
                printf("当前情况:%f/%f",fridge_used,fridge_volume);
                return  ;
            }
            else if (new_volume<0)
            {
                printf("?虽然我的数学不太好，但是我知道，体积不能为负数啊喂！?\n");
                return ;
            }
            else if (change==0)
            {
                printf("冰箱酱真不理解人类的思维，没变体积也要修改吗qwq\n");
                return ;
            }
            pf->food_volume=new_volume;
            fridge_used+=change;
            printf("体积更新成功，现在的体积是 %f/%f 喵~\n",fridge_used,fridge_volume);
            break;
        }
        case(2):
        {
            float old_temperature=pf->safe_temperature;  //保存原来的温度
            float new_temperature;                       //设定新的温度
            printf("现在冰箱酱的温度是:%f",old_temperature);
            printf("输入新的温度喵:");
            scanf("%f",&new_temperature);
            float change_=0.0;
            change_=new_temperature-old_temperature;
            if(new_temperature<-20||new_temperature>10)
            {
                printf("冰箱酱和食物不能接受低于-20摄氏度或高于10摄氏度的环境喵~！(╯▔皿▔)╯\n");
                printf("当前情况:%f/%f",fridge_temperature);
                return ;
            }
            
            else if (change_==0)
            {
                printf("冰箱酱真不理解人类的思维，没变温度也要修改吗qwq\n");
                return ;
            }
            pf->safe_temperature=new_temperature;
            struct Foods * temp=headf;
            float lowest=10.0;          //设定最有可能的最低温度
            while(temp!=NULL)
            {
                if (pf->safe_temperature<lowest)
                {
                    lowest=pf->safe_temperature;
                }
                temp=temp->next;
            }
            fridge_temperature=lowest;
            printf("温度更新成功，现在的温度是 %f 喵~\n",fridge_temperature);
            break;
        }
        case(3):
        {
            int new_type;
            printf("你是不是一开始输入错了，当前种类是:");
            switch(pf->type)
            {   
                
                case(0): printf("蔬菜喵~\n"); break;
                case(1): printf("肉类喵~\n"); break;
                case(2): printf("水果喵~\n"); break;
            }
            printf("请输入新的种类 喵~\n");
            printf("0为蔬菜喵~\n");
            printf("1为肉类喵~\n");
            printf("2为水果喵~\n");
            printf("输入:");
            scanf("%d",&new_type);
            if (new_type<0||new_type>2)
            {
                printf("输入错误喵~！\n");
                return ;
            }
            
            pf->type = new_type;
            printf("种类修改成功喵~！\n");
            break;
        }
        case(4):        //取消修改
        {
            printf("取消修改了哦~");
            break;
        }
        default:
        {
            printf("何意味，输入出错了啊啊啊\n");
            break;
        }
    }
}

void  tips(struct Foods* headf)
{
    if (headf==NULL)
    {
        printf("冰箱酱里空空如也~喵~\n");
        return;
    }
    int veg_count=0, mea_count=0,fru_count=0;
    struct Foods *pf=headf;

    while(pf!=NULL)
    {
        switch(pf->type)
        {
            case(0): veg_count++; break;
            case(1): mea_count++; break;
            case(2): fru_count++; break;
        }
        pf=pf->next;
    }
    pf=headf;
    if (veg_count>=mea_count)
    {
        printf("建议做蔬菜汤~\n");
        printf("蔬菜汤有助于补充营养、增强抵抗力和消化能力 喵~\n");
    }
    else if (mea_count>=veg_count)
    {
        printf("建议做肉汤~\n");
        printf("肉汤有助于补充蛋白质、补充矿物质 喵~\n");
    }
    else if (abs(fridge_temperature - pf->safe_temperature)>5)
    {
        printf("这个温度差距有点大，不太适合食物保存 喵~\n");
        printf("建议稍微调整一下温度\n");
    }
    else if (pf->food_volume>fridge_volume*0.382)        //1-黄金分割比的数值
    {
        printf("该食物貌似有点大qwq\n");
        printf("建议进行分割大小操作喵~\n");
    }
}

void free_list(struct Foods* headf)             //销毁链表
{
    struct Foods* p = headf;
    while (p != NULL)
    {
        struct Foods* next = p->next;
        free(p);
        p = next;
    }
}

struct Foods* append_list(struct Foods* headf, struct Foods* new_headf)     //将新链表加到原有链表的后面
{
    struct Foods* p;

    if (headf == NULL) return new_headf;
    if (new_headf == NULL) return headf;

    p = headf;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = new_headf;
    return headf;
}

void save_data(struct Foods* headf)
{
    FILE* fp;
    struct Foods* p;
    int count = 0;

    fp = fopen("fridge.dat", "wb");
    if (fp == NULL)
    {
        printf("文件打不开喵~ 保存失败QAQ\n");
        return;
    }

    // 统计数量
    p = headf;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    // 保存冰箱全局信息
    fwrite(&fridge_volume, sizeof(float), 1, fp);
    fwrite(&fridge_used, sizeof(float), 1, fp);
    fwrite(&fridge_temperature, sizeof(float), 1, fp);

    // 保存食物数量
    fwrite(&count, sizeof(int), 1, fp);

    // 保存每个食物
    p = headf;
    while (p != NULL)
    {
        fwrite(p->name, sizeof(char), 500, fp);
        fwrite(&p->food_volume, sizeof(float), 1, fp);
        fwrite(&p->safe_temperature, sizeof(int), 1, fp);
        fwrite(&p->type, sizeof(int), 1, fp);
        p = p->next;
    }

    fclose(fp);
}

struct Foods* load_data()
{
    FILE* fp;
    struct Foods* headf = NULL;
    struct Foods* tail = NULL;
    struct Foods* pf;
    int count;
    int i;

    fp = fopen("fridge.dat", "rb");
    if (fp == NULL)
    {
        return NULL;   // 没文件，第一次运行
    }

    // 读取冰箱全局信息
    if (fread(&fridge_volume, sizeof(float), 1, fp) != 1) { fclose(fp); return NULL; }
    if (fread(&fridge_used, sizeof(float), 1, fp) != 1) { fclose(fp); return NULL; }
    if (fread(&fridge_temperature, sizeof(float), 1, fp) != 1) { fclose(fp); return NULL; }

    // 读取数量
    if (fread(&count, sizeof(int), 1, fp) != 1) { fclose(fp); return NULL; }

    for (i = 0; i < count; i++)
    {
        pf = (struct Foods*)malloc(sizeof(struct Foods));
        if (pf == NULL)
        {
            fclose(fp);
            free_list(headf);
            return NULL;
        }

        fread(pf->name, sizeof(char), 500, fp);
        fread(&pf->food_volume, sizeof(float), 1, fp);
        fread(&pf->safe_temperature, sizeof(int), 1, fp);
        fread(&pf->type, sizeof(int), 1, fp);

        pf->next = NULL;

        if (headf == NULL)
        {
            headf = pf;
            tail = pf;
        }
        else
        {
            tail->next = pf;
            tail = pf;
        }
    }

    fclose(fp);
    return headf;
}



