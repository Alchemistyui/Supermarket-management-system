

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PRODUCTS 100
#define MAX_PRODUCT_NAME 15
#define MAX_PRODUCT_ID 15



typedef enum Status{
    ERROR = 0, OK = 1
}Status;


typedef struct Product{
    char id[MAX_PRODUCT_ID];
    char name[MAX_PRODUCT_NAME];
    int price;
    int sumAmount;
    int remaining;
}Product;



typedef struct ProductBase{
    Product temp;
    Product productArray[MAX_PRODUCTS];
    int numOfProduct;
}ProductBase;





Status Initialize(const char* fileName, ProductBase* pProductBase);
void   InputExample(void);
Status Modify(ProductBase* pProductBase, char* name);
Status Delet(ProductBase* pProductBase, char* name);
Status SearchByName(ProductBase* pProductBase, char* string);
Status SearchByID(ProductBase* pProductBase, char* string);
void   PrintProduct(Product* pProduct);
void   PrintProductBase(ProductBase* pProductBase);
Status ReadInsertMessage(ProductBase* pProductBase);
Status Insert(ProductBase* pProductBase);
void Bubble(ProductBase* pProductBase);
Status Save(const char* fileName, ProductBase* pProductBase);






Status Initialize(const char* fileName, ProductBase* pProductBase){
    int i = 0;
    FILE* pProductFile;
    pProductFile = fopen(fileName, "r");
    if(pProductFile == NULL){
        return ERROR;
    }
    while(!feof(pProductFile) && i < MAX_PRODUCTS){
        fscanf(pProductFile, "%s\t%s%d%d%d",
               pProductBase -> productArray[i].id,
               pProductBase -> productArray[i].name,
               &pProductBase -> productArray[i].price,
               &pProductBase -> productArray[i].sumAmount,
               &pProductBase -> productArray[i].remaining);
        i++;
    }
    pProductBase -> numOfProduct = i - 1;
    return OK;
}




void   InputExample(void){
    printf("输入示例：\n");
    printf("商品ID：2\n商品名称：milk\n商品价格：233\n商品折扣：0.5\n商品数目：233\n商品余数：2\n");
}




Status Modify(ProductBase* pProductBase, char* name){
    int i, a;
    
    for(i = 0; i < MAX_PRODUCTS; i++){
        if (strcmp(pProductBase -> productArray[i].name, name) == 0){

            printf("选择您想修改的信息：\n");
            printf("1.商品ID\n2.商品价格\n3.商品数目\n4.商品余数\n");
            
            scanf("%1d", &a);
            switch (a){
                case 1:
                    printf("请输入新的商品ID（15个字节以内）\n");
                    scanf("%s", pProductBase -> productArray[i].id);
                    break;
                case 2:
                    printf("请输入新的商品价格\n");
                    scanf("%d", &pProductBase -> productArray[i].price);
                    break;
            
                case 3:
                    printf("请输入新的商品数目\n");
                    scanf("%d", &pProductBase -> productArray[i].sumAmount);
                    break;
                case 4:
                    printf("请输入新的商品余数\n");
                    scanf("%d", &pProductBase -> productArray[i].remaining);
                    break;
                default:
                    printf("请输入正确的操作！\n");
                    break;
                    
            }
            
            return OK;
        }
    }
    
    return ERROR;
    
}




Status Delet(ProductBase* pProductBase, char* string){
    int i, j;
    
    for(i = 0; i < MAX_PRODUCTS; i++){
        if (strcmp(pProductBase -> productArray[i].name, string) == 0){
            for(j = i; j < (pProductBase ->numOfProduct); j++){
                pProductBase -> productArray[j] = pProductBase -> productArray[j+1];
            }
            
            pProductBase ->numOfProduct-= 1;
            return OK;
        }
    }
    
    
    
    return ERROR;
}






Status SearchByName(ProductBase* pProductBase, char* string){
    int i;
    
    
    for(i = 0; i < (pProductBase ->numOfProduct); i++){
        if (strcmp(pProductBase -> productArray[i].name, string) == 0){
            PrintProduct(&pProductBase -> productArray[i]);
            return OK;
        }
    }

    
    return ERROR;
}


Status SearchByID(ProductBase* pProductBase, char* string){
    int i;
    
    
    for(i = 0; i < (pProductBase ->numOfProduct); i++){
        if (strcmp(pProductBase -> productArray[i].id, string) == 0){
            PrintProduct(&pProductBase -> productArray[i]);
            return OK;
        }
    }
    
    return ERROR;

}



void PrintProduct(Product* pProduct){
    printf("商品ID：%s\t商品名称：%s\t商品价格：%d\t商品数目：%d\t商品余数：%d\n",
           pProduct -> id,
           pProduct -> name,
           pProduct -> price,
           pProduct -> sumAmount,
           pProduct -> remaining);
    return ;
}





void   PrintProductBase(ProductBase* pProductBase){
    int i = 0;
    
    for(i = 0; i < (pProductBase ->numOfProduct); i++){
        PrintProduct(&(pProductBase ->productArray[i]));
    }

    
}



Status ReadInsertMessage(ProductBase* pProductBase){
    
    printf("输入您要插入的商品信息（换行以区分商品条目）:\n");
    InputExample();
    printf("商品ID（15个字节以内）:\n");
    scanf("%s", pProductBase -> productArray[pProductBase ->numOfProduct].id);
    printf("商品名称（15个字节以内）:\n");
    scanf("\n%s", pProductBase -> productArray[pProductBase ->numOfProduct].name);
    printf("商品价格:\n");
    scanf("%d", &pProductBase -> productArray[pProductBase ->numOfProduct].price);
    printf("商品数目:\n");
    scanf("%d", &pProductBase -> productArray[pProductBase ->numOfProduct].sumAmount);
    printf("商品余数:\n");
    scanf("%d", &pProductBase -> productArray[pProductBase ->numOfProduct].remaining);
    return OK;

}



Status Insert(ProductBase* pProductBase){
    int i;
    
    
    if((ReadInsertMessage(pProductBase)) == ERROR){
        return ERROR;
    }
    
    pProductBase ->numOfProduct++;
    
    for(i = 0; i < pProductBase ->numOfProduct; i++){
        if(strcmp(pProductBase -> productArray[i].id, pProductBase -> productArray[0].name) == 0){
            
            pProductBase ->numOfProduct--;
            return ERROR;
        }
    }
    Bubble(pProductBase);
    
    return OK;
}






void Bubble(ProductBase* pProductBase){
    int i, j;
    
    //冒泡排序！
    for(i = 0; i < (pProductBase ->numOfProduct); i++){
        for(j = 0; j < (pProductBase ->numOfProduct) - 1 - i; j++){
            if(strcmp(pProductBase -> productArray[j].id,
                      pProductBase -> productArray[j+1].id) >= 0){
                pProductBase -> temp = pProductBase -> productArray[j];
                pProductBase -> productArray[j] = pProductBase -> productArray[j+1];
                pProductBase -> productArray[j+1] = pProductBase -> temp;
            }
        }
    }
    
    PrintProductBase(pProductBase);
    return ;
    
}





Status Save(const char* fileName, ProductBase* pProductBase){
    int i;
    char empty = '0';
    FILE* pFile;
    pFile = fopen(fileName, "w");
    if(pFile == NULL){
        return ERROR;
    }
    
    for(i = 0; i < (pProductBase ->numOfProduct); i++){
    if(strcmp(pProductBase -> productArray[i].name, &empty) != 0){
            fprintf(pFile, "%s   %s   %d   %d   %d\n",
                  pProductBase -> productArray[i].id,
                  pProductBase -> productArray[i].name,
                  pProductBase -> productArray[i].price,
                  pProductBase -> productArray[i].sumAmount,
                  pProductBase -> productArray[i].remaining);
        
    }
    }
        fclose(pFile);
        return OK;
    

}





int main(int argc, const char * argv[]) {
    
    int a, b;
    char name[MAX_PRODUCT_NAME];
    ProductBase ProductBase;
    
    
    if(Initialize("/Users/ryshen/Desktop/info.txt",&ProductBase) != OK){
        printf("初始化失败！\n\n");
    }
    
    
    for( ; ; ){
        
        printf("超市商品管理系统\n");
        printf("****************************\n");
        printf("请输入操作：\n");
        printf("1.商品信息的初始化\n2.商品信息修改\n3.商品信息删除\n4.商品信息的排序\n");
        printf("5.商品信息查找\n6.商品信息的插入\n7.显示全部信息\n8.退出系统并保存\n");
        printf("****************************\n");
        printf("输入您的选择\n");
        scanf("%1d", &a);
        
        switch(a){
            case 1:
                if(Initialize("/Users/ryshen/Desktop/info.txt",&ProductBase) != OK){
                    printf("初始化失败！\n\n");
                }
                else{
                    printf("初始化成功！\n\n");
                }
                break;
            case 2:
                printf("请输入您要修改的商品名称：(15个字节以内）\n");
                scanf("%s", name);
                if(Modify(&ProductBase, name) != OK){
                    printf("您要修改的商品不存在！\n\n");
                }
                else{
                    printf("修改信息成功！\n\n");
                }
                break;
            case 3:
                printf("请输入您要删除的商品：(15个字节以内）\n");
                scanf("%s", name);
                if(Delet(&ProductBase, name) != OK){
                    printf("您要删除的商品信息不存在！\n\n");
                }
                else{
                    printf("删除商品信息成功！\n\n");
                }
                break;
            case 4:
                Bubble(&ProductBase);
            case 5:
                printf("请输入您要查询的商品：\n");
                scanf("%s", name);
                printf("请选择查找商品的方式：\n");
                printf("1.商品名称\t2.商品ID\n");
                scanf("%d", &b);
                switch(b){
                    case 1:
                        if(SearchByName(&ProductBase, name) != OK){
                            printf("您要查询的商品不存在！\n\n");
                        }
                        break;
                    case 2:
                        if(SearchByID(&ProductBase, name) != OK){
                            printf("您要查询的商品不存在！\n\n");
                        }
                        break;
                    default:
                        printf("请输入正确的操作");
                        break;
                }
                break;
            case 6:
                if(Insert(&ProductBase) != OK){
                    printf("此商品已存在！\n\n");
                }
                else{
                    printf("插入信息成功！\n\n");
                }
                break;
            
            case 7:
                PrintProductBase(&ProductBase);
                break;
            case 8:
                if(Save("/Users/ryshen/Desktop/info.txt", &ProductBase) != OK){
                    printf("保存信息失败！\n\n");
                }
                else{
                    printf("保存信息成功！\n\n");
                    return 0;
                }
                break;
            default:
                printf("请输入正确的操作！\n\n");
                return 0;
                break;

        }
        
    }
    return 0;
}
                  
                  
                  
                  


                  
         
                  
                  
                  
                  
                  
                  
