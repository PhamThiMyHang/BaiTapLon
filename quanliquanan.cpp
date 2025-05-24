                               //Ten: PHAM THI MY HANG
                               //MSSV: 6551071028
#include"stdio.h"
#include "string.h"
#include"stdlib.h"
#include"math.h"
typedef struct Food{
	int STT;
	char name[175];
	int  price;
    struct	Food *next;
}Food;

typedef struct mon{
	int MaFood;
	int Number;
	struct mon *next;
}mon;

typedef struct Table{
	mon *food;
	int Tonggiatien;
}Table;

void CheckImput(char *a,int n){
	int i;
	if(strlen(a)==n){
		if(a[strlen(a)-1]!='\n'){
			printf("Tran bo nho\n ");
			for(i=1;i<strlen(a)-1;i++){
				if(a[strlen(a)-1]!=' '){
					break;
				}
			}
			a[strlen(a)-i+1]='\0';
			printf("Name: %s\n ",a);
		}else{
			for(i=2;i<strlen(a)-1;i++){
				if(a[strlen(a)-i]!=' '){
					break;
				}
			}
			a[strlen(a)-i+1]='\0';
		}
	}else{
		for(i=2;i<strlen(a)-1;i++){
			if(a[strlen(a)-i]!=' '){
				break;
			}
		}
		a[strlen(a)-i+1]='\0';
	}
}

Food *NewFood(char *a){
	Food *f;
	f=(Food*)malloc(sizeof(Food));
	strcpy(f->name,a);
	printf("Price: ");
	scanf("%d",&f->price);
	fflush(stdin);
	f->next=NULL;
	return f;
}

void ListFood(Food **f,int *n){
	*f=NULL;
	Food *fdau;
	fdau=*f;
	*n=0;
	while((*n)<=100){
		printf("\n ");
		printf("Name Food: ");
		char a[175];
		fgets(a,175,stdin);
		CheckImput(a,174);
		if(a[0]=='\0'){
			printf("Stop");
			break;
		}
		if(fdau==NULL){
			fdau=NewFood(a);
			fdau->STT=(*n)+1;
			*f=fdau;
		}else{
			(*f)->next=NewFood(a);
			(*f)->next->STT=(*n)+1;
			*f=(*f)->next;
		}
		(*n)++;
		if(*n==99){
			printf("Menu khong vuot qua 100.\n ")	;
		}
	}
	printf("HoanThanh\n ");
	*f=fdau;
	return;
}

int CheckMon(Food*f,char*a);

void ThemCuoi(Food **s,int *n){
	Food *sdau;
	sdau=*s;
	while(*n<100){
		printf("\n ");
		printf("Name Food: ");
		char a[175];
		fgets(a,175,stdin);
		CheckImput(a,174);
		if(a[0]=='\0'){
			printf("Stop Them\n ");
			break;
		}
		if(CheckMon(sdau,a)==0){
			if(sdau==NULL){
				sdau=NewFood(a);
				sdau->STT=(*n)+1;
				*s=sdau;
			}else{
				while((*s)->next!=NULL){
					*s=(*s)->next;
				}
				(*s)->next=NewFood(a);
				(*s)->next->STT=(*n)+1;
				*s=(*s)->next;
			}
			(*n)++;
			if(*n==100){
				printf("Vuot gioi han\n ");
			}
		}else{
			printf("Trung\n ");	
			printf("Ket thuc.\n ");
			break;
		}
	}
	*s=sdau;
}

void ThemList(Food **s,int *n){
	if(*n>=100){
		printf("List da dat den muc gioi han\n ");
		return;
	}else{
		ThemCuoi(s,n);
	}
}


//Xap Sep
int CheckViTriTheoPrice(Food *s_now,Food *s_dau){
	Food *s;
	s=s_dau;
	int n=0;
	do{
		if(s_now->price>s->price){
			n++;
		}
		s=s->next;
	}while(s!=NULL);
	return n;
}

int CheckViTriTheoName(Food *s_now,Food *s_dau){
	Food *s;
	s=s_dau;
	int n=0;
	do{
		if(stricmp(s_now->name,s->name)>0){
			n++;
		}
		s=s->next;
	}while(s!=NULL);
	return n;
}

int CheckViTriTheoSTT(Food *s_now,Food *s_dau){
	Food *s;
	s=s_dau;
	int n=0;
	do{
		if(s_now->STT>s->STT){
			n++;
		}
		s=s->next;
	}while(s!=NULL);
	return n;
}

Food *coppy(Food *s){
	Food *temp;
	temp=(Food*)malloc(sizeof(Food));
	strcpy(temp->name,s->name);
	temp->price=s->price;
	temp->STT=s->STT;
	temp->next=NULL;
	return temp;
}

void HoanDoi (Food *s1,Food *s2){
	Food *temp;
	temp = coppy(s1);
	strcpy(s1->name,s2->name);
	s1->price=s2->price;
	s1->STT=s2->STT;
	strcpy(s2->name,temp->name);
	s2->price=temp->price;
	s2->STT=temp->STT;
	free(temp);
}

void  XapSepTheoSTT(Food *s){
	if(s==NULL){
		printf("DanhSachRong.\n ");
		return;
	}
	Food *sdau;
	sdau=s;
	int i=0;
	float STT=0;// kiem tra neu mu cua node truoc da nam dung vi tri r, ma node tiep theo lap lai thi bo qua xet toi node khac
	while(s!=NULL){
		int n;
		n=CheckViTriTheoSTT(s,sdau);
		if(n==i){
			i++;
			STT=s->STT;
			s=s->next;
			continue;
		}else if(i!=0 && STT==s->STT){
			i++;
			STT=s->STT;
			s=s->next;
			continue;
		}else{
			Food *temp;
			temp=sdau;
			int j=0;
			while(j<n){
				temp=temp->next;
				j++;
			}
			j=0;
			if(temp->STT==s->STT){
				do{
					temp=temp->next;
					j++;
				}while(temp->STT== s->STT);
			}
			if(j!=0){
				if(n<i&&i<n+j){
					i++;
					s=s->next;
				}else{
					HoanDoi(s,temp);
					i++;
					s=s->next;
				}
			}else{
				HoanDoi(s,temp);
			}
		}
		
	}
	s=sdau;
//	printf("Hoan Thanh xs\n ");
}

void  XapSepTheoName(Food *s){
	if(s==NULL){
		printf("DanhSachRong.\n ");
		return;
	}
	Food *sdau;
	sdau=s;
	int i=0;
	char Name[175];
	while(s!=NULL){
		int n;
		n=CheckViTriTheoName(s,sdau);
		if(n==i){
			i++;
			strcpy(Name,s->name);
			s=s->next;
			continue;
		}else if(i!=0 && stricmp(Name,s->name)==0){
			i++;
			strcpy(Name,s->name);
			s=s->next;
			continue;
		}else{
			Food *temp;
			temp=sdau;
			int j=0;
			while(j<n){
				temp=temp->next;
				j++;
			}
			j=0;
			if(stricmp(Name,s->name)==0){
				do{
					temp=temp->next;
					j++;
				}while(stricmp(Name,s->name)==0);
			}
			if(j!=0){
				if(n<i&&i<n+j){
					i++;
					s=s->next;
				}else{
					HoanDoi(s,temp);
					i++;
					s=s->next;
				}
			}else{
				HoanDoi(s,temp);
			}
		}
		
	}
	s=sdau;

//	printf("Hoan Thanh xs\n ");
}

void  XapSepTheoPrice(Food *s){
	if(s==NULL){
		printf("DanhSachRong.\n ");
		return;
	}
	Food *sdau;
	sdau=s;
	int i=0;
	float Price=0;// kiem tra neu mu cua node truoc da nam dung vi tri r, ma node tiep theo lap lai thi bo qua xet toi node khac
	while(s!=NULL){
		int n;
		n=CheckViTriTheoPrice(s,sdau);
		if(n==i){
			i++;
			Price=s->price;
			s=s->next;
			continue;
		}else if(i!=0 && Price==s->price){
			i++;
			Price=s->price;
			s=s->next;
			continue;
		}else{
			Food *temp;
			temp=sdau;
			int j=0;
			while(j<n){
				temp=temp->next;
				j++;
			}
			j=0;
			if(temp->price==s->price){
				do{
					temp=temp->next;
					j++;
				}while(temp->price== s->price);
			}
			if(j!=0){
				if(n<i&&i<n+j){
					i++;
					s=s->next;
				}else{
					HoanDoi(s,temp);
					i++;
					s=s->next;
				}
			}else{
				HoanDoi(s,temp);
			}
		}
		
	}
	s=sdau;
//	printf("Hoan Thanh xs\n ");
}
//Lam viec voi file
void XuatFile(Food *s,int n){
 	FILE *fvb;
 	fvb=fopen("Menu.text","w");
 	if(fvb==NULL){
 		printf("Mo tep that bai.\n ");
 		return;
	 }
	 if(s==NULL){
	 	fprintf(fvb,"%d\n ",n);
	 	fclose(fvb);
	 	return;
	 }else{
	 	fprintf(fvb,"%d\n",n);
	 	Food *sdau;
	 	sdau=s;
	 	do{
	 		fprintf(fvb,"%d\n",s->STT);
	 		fprintf(fvb,"%s\n",s->name);
	 		fprintf(fvb,"%d\n",s->price);
	 		s=s->next;
		 }while(s!=NULL);
		 fclose(fvb);
		 s=sdau;
	 }
 }
 
Food *DocMenuTuFile(int *n){
	FILE *fvb;
	fvb=fopen("Menu.text","r");
	if(fvb==NULL){
		printf("Mo tep that bai.\n ");
		return NULL;
	}
	fscanf(fvb,"%d",n);
	printf("So thuc an: %d \n",*n);
	getc(fvb);
	Food *s;
	s=NULL;
	Food *sdau;
	sdau=s;
	while(feof(fvb)==0){
		char a[4];
		if(fgets(a,4,fvb)==NULL){
			s=NULL;
			break;
		}
		if(sdau==NULL){
			sdau=(Food*)malloc(sizeof(Food));
			s=sdau;
		}else{
			s->next=(Food*)malloc(sizeof(Food));
			s=s->next;
		}
		s->STT=atoi(a);
		fgets(s->name,175,fvb);
		CheckImput(s->name,174);
		fscanf(fvb,"%d",&s->price);
		fgetc(fvb);
		s->next=NULL;
	}
	fclose(fvb);
	s=sdau;
	return s;
	
} 

void XoaGiua(Food **h,int n,int *i){
	Food *hdau;
	hdau=*h;
	Food *hbefore;
	while(n>1){
		if((*h)->next==NULL){
			printf("Xac dinh vi tri mon an sai. \n");
			*h=hdau;
			return;
		}else{
			hbefore=*h;
			*h=(*h)->next;
		}
		n--;
	}
	if((*h)->next==NULL){
		Food *temp;
		temp=*h;
		hbefore->next=NULL;
		free(temp);
		*h=hdau;
		*i=(*i)-1;
	}else{
		Food *temp;
		temp=*h;
		hbefore->next=(*h)->next;
		free(temp);
		*h=hbefore->next;
		do{
			(*h)->STT=(*h)->STT-1;
			*h=(*h)->next;
		}while(*h!=NULL);
		*h=hdau;
		*i=(*i)-1;
		return; 
	}
}
void XoaDau(Food **h,int *n){
	Food *temp;
	temp=*h;
	*h=(*h)->next;
	free(temp);
	Food* hdau=*h;
	do{
		(*h)->STT=(*h)->STT-1;
			*h=(*h)->next;
	}while(*h!=NULL);
	*h=hdau;
	*n=(*n)-1;
}
void ChinhSuaSTT(Food *s_now,int n,Food *s_dau){
	int temp=s_now->STT;
	do{
		printf("Nhap vao STT: ");
		scanf("%d",&s_now->STT);
		fflush(stdin);
	}while(s_now->STT<=0);
	printf("\nVao\n ");
	if(s_now->STT>n){
		s_now->STT=n;
	}
	if(s_now->STT==temp){
		return;
	}else if(s_now->STT<temp){
		Food *sdau;
		sdau=s_dau;
		while(temp>1){
			sdau=sdau->next;
			temp--;
		}do{
			sdau->STT=sdau->STT+1;
			sdau=sdau->next;
		}while(sdau->STT!=s_now->STT);
	}else{

		Food *s;
		s=s_now->next;
		do{
			if(s->STT==s_now->STT){
				s->STT=s->STT-1;
				break;
			}
			s->STT=s->STT-1;
			s=s->next;
		}while(s!=NULL);
	}
}

void ChinhSuaPrice(Food *s_now){
	do{
		printf("Nhap Price: ");
		scanf("%d",&s_now->price);
		fflush(stdin);
	}while(s_now->price<0);
}
int CheckMon(Food*f,char*a);

void ChinhSuaName(Food *s_now,Food *s_dau){
	printf("Nhap vao Ten mon an moi ");
	char a[175];
	fgets(a,175,stdin);
	CheckImput(a,174);
	if(a[0]=='\0'){
		printf("Khong ton tai");
		return;
	}
	if(CheckMon(s_dau,a)==0){
		strcpy(s_now->name,a);
		return;
	}else{
		printf("Trung\n ");
	}
}


void ChinhSua(Food **f,int *n){
	if(*f==NULL){
		printf("Thuc Don Rong.\n ");
		return;
	}else{
		printf("vao");
		while(1){
			printf("Nhap vao Ten mon an can chinh sua ");
			char a[175];
			fgets(a,175,stdin);
			CheckImput(a,174);
			if(a[0]=='\0'){
				printf("Hoan thanh chinh sua.\n ");
				break;
			}
			int i=CheckMon(*f,a);
			if(i==0){
				printf("Khong ton tai\n ");
				continue;
			}else{
				Food *sdau;
				sdau=*f;
				int j;
				j=i;
				while(j>1){
					*f=(*f)->next;
					j--;
				}
				int choice ;
				do{
					printf("1.Sua.\n ");
					printf("2.Xoa.\n ");
					printf("3. thoat\n ");
					scanf("%d",&choice);
					fflush(stdin);
				}while(choice<1 ||choice >3);
				switch (choice){
					case 1:{
						do{
						printf("1.Sua STT.\n ");
						printf("2.Sua Name.\n ");
						printf("3.Sua Price.\n ");
						printf("4.Thoat.\n ");
						scanf("%d",&choice);
						fflush(stdin);
						}while(choice<1 ||choice >4);
						switch (choice){
							case 1:{
								ChinhSuaSTT(*f,*n,sdau);
								*f=sdau;
								break;
							}
							case 2:{
								ChinhSuaName(*f,sdau);
								*f=sdau;
								break;
							}
							case 3:{
								ChinhSuaPrice(*f);
								*f=sdau;
								break;
							}
							case 4:{
								*f=sdau;
								return;
								break;
							}
						}
						break;
					}
					case 2:{
						if(i==1){
							XoaDau(f,n);
						}else{
							*f=sdau;
							XoaGiua(f,i,n);
						}
						break;
					}
					case 3:{
						printf("Ket Thuc\n ");
						return;
						break;
					}
				}
			}
		}
		
		
	}
}

//Tao duong gach co bang cua bang
void Bang(int n,int dong){
	if(dong==1){
		printf("\n ");
		for(int i=1;i<=n;i++){
			if(i==n){
				printf("_\n ");
			}else{
			printf("_");
		}
	}
	}else{
		for(int i=1;i<=n;i++){
			if(i==n){
				printf("|\n ");
			}else if(i==1){
				printf("|");
			}else if (i==ceil((2*n)/3)+1){
				printf("|");
			}
			else{
				printf("_");
			}
		}
	}
}
//th 1: dong binh thuong; th2 dong dau menu
void chu(char *a,int n,int th, int ve ){
	if(th==1){
		printf("|");
	}
	if(strlen(a)<n){
		printf("%s",a);
		for(int i=1;i<n-strlen(a);i++){
			printf(" ");
		}
		if(ve==1){
			printf("|");
		}else{
			printf("|\n ");
		}
	}
}

int SoChuSo(int n){
	int s=1;
	while(n!=0){
		n=n/10;
		s++;
	}
	return s;
}

void So(int a,int n,int m){
	if(m<n){
		printf("%d",a);
		for(int i=1;i<n-m+1;i++){
			printf(" ");
		}
		printf("|\n ");//sua \n
		 
	}
}

void XuatMenuFood(Food *f){
	Food *fdau;
	fdau=f;
	if(f==NULL){
		printf("DS rong\n ");
	}else{
		printf("\n");
		Bang(88,1);
		char a[]="NameFood";
		chu(a,(2*88)/3,1,1);
		char b[]="Price";
		chu(b,(1*88)/3,2,2);
		Bang(88,2);
		 do{
		 	chu(f->name,(2*88)/3,1,1);
		 	So(f->price,(1*88)/3,SoChuSo(f->price));
		 	Bang(88,2);
		 	f=f->next; 
		 }while(f!=NULL);
	}
	printf("HoanThanh\n ");
	f=fdau;
	
}
//Chon so ban
void SoBan(int *n){
	do{
		printf("Nhap vao so ban an cua quan: ");
		scanf("%d",n);
		fflush(stdin);
	}while(*n<0 ||*n>5);
	FILE*fvb;
	fvb=fopen("SoBan.text","w");
	fprintf(fvb,"%d",*n);
	fclose(fvb);
}

int DocSoBan(int *n){
	FILE*fvb;
	fvb=fopen("SoBan.text","r");
	if(fvb==NULL){
		printf("Chua nhap so ban.\n ");
		return 0;	
	}
	fscanf(fvb,"%d",n);
	fclose(fvb);
	return *n;
}

int ChonBan(int n){
	for(int i=1;i<=n;i++){
		printf("Ban %d \n",i);
	}
	int i=0;
	do{
		scanf("%d",&i);
		fflush(stdin);
	}while(i<1 ||i>n);
	return i;
}

int CheckMon(Food *s,char *a){
	if(s==NULL){
//		printf("Khong ton tai menu \n ");
		return 0; 
	}else{
		Food *sdau;
		sdau=s;
		do{
			if(strcmpi(a,s->name)==0){
				int i=s->STT;
				s=sdau;
				return i;
			}
			s=s->next;
		}while(s!=NULL);
		s=sdau;
		return 0;
	}
}
//Kiem tra xem ten thuc an nhap vao co bi trung vs cac mon da chon truoc do hay khong neu co thi tang so luong cua mon an, neu khong thi them vao danh sach mon an 
int CheckMap(int *a, int n,int max){
	int j=max;
	for(max;max>=0;max--){
		if(*(a+max)==n){
			return max;
		}
	}
	return j+1;
}
int ChonMon(Table *t,int j,Food *s){
	int *an;
	an=(int*)malloc(150*sizeof(int));
	int *so;
	so=(int*)calloc(150,sizeof(int));
	int i=-1;
	int max=i;
	while(1){
		printf("Nhap vao Ten mon an ");
		char a[175];
		fgets(a,175,stdin);
		CheckImput(a,174);
		if(a[0]=='\0'){
			printf("HoanThanhChonMon\n ");
			break;
		}
		if(CheckMon(s,a)==0){
			printf("Khong ton tai\n ");
			continue;
		}else{
			i=CheckMap(an,CheckMon(s,a),max);
			if(i>max){
				max=i;
			}
			*(an+i)=CheckMon(s,a);
			printf("Nhap So luong: ");
			int k;
			scanf("%d",&k);
			fflush(stdin);
			*(so+i)=*(so+i)+k;
		}
	}
	(t+j-1)->food=NULL;
	mon *fdau;
	fdau=(t+j-1)->food;
	int k=0;
	while(k<=max){
		if(fdau==NULL){
			fdau=(mon*)malloc(sizeof(mon));
			(t+j-1)->food=fdau;
		}else{
			(t+j-1)->food->next=(mon*)malloc(sizeof(mon));
			(t+j-1)->food=(t+j-1)->food->next;
		}
		(t+j-1)->food->MaFood=*(an+k);
		printf(" Ma %d\n ",(t+j-1)->food->MaFood);
		(t+j-1)->food->Number=*(so+k);
		printf("So Luong %d\n ",(t+j-1)->food->Number);
		(t+j-1)->food->next=NULL;
		k++; 
	}
	(t+j-1)->food=fdau;
/*	while((t+j-1)->food!=NULL){
		printf(" Ma %d\n ",(t+j-1)->food->MaFood);
		printf("So Luong %d\n ",(t+j-1)->food->Number);
		(t+j-1)->food=(t+j-1)->food->next;
	}
	(t+j-1)->food=fdau;*/
	free(so);
	free(an);
	return max;
}
//Dung cho chuwcs nawng tinhs toans nhanh tong tien da chon
//Co the viet lai de tiet kiem thoi gian
int ChotT(int n,int m,Food *s){
	Food *sdau;
	sdau=s;
	int i=1;
	while(1){
		if(i==n){
			int j=m*((s->price));
			s=sdau;
			return j;
		}
		s=s->next;
		i++;
	}
}
void ChotTien(int max,Table *t,int j,Food *s){
	mon *fdau;
	fdau=(t+j-1)->food;
	(t+j-1)->Tonggiatien=0;
	while((t+j-1)->food!=NULL){
		(t+j-1)->Tonggiatien=(t+j-1)->Tonggiatien+ChotT((t+j-1)->food->MaFood,(t+j-1)->food->Number,s);
		(t+j-1)->food=(t+j-1)->food->next;
	}
	(t+j-1)->food=fdau;
	printf("Tong: %d\n",(t+j-1)->Tonggiatien);
	
}
int Chot(int n,int m,Food *s){
	Food *sdau;
	sdau=s;
	int i=1;
	while(1){
		if(i==n){
			printf("Name: %s      ",s->name);
			printf("SL: %d     ",m);
			printf("Gia: %d    \n ",s->price);
			int j=m*((s->price));
			s=sdau;
			return j;
		}
		s=s->next;
		i++;
	}
}
void ListChot(int max,Table *t,int j,Food *s){
	printf("Danh sach :\n ");
	//int T=0;
	mon *fdau;
	fdau=(t+j-1)->food;
	(t+j-1)->Tonggiatien=0;
	while((t+j-1)->food!=NULL){
		int h=Chot((t+j-1)->food->MaFood,(t+j-1)->food->Number,s);
		(t+j-1)->Tonggiatien=(t+j-1)->Tonggiatien+h;
		(t+j-1)->food=(t+j-1)->food->next;
	}
	printf("Tong Tien: %d \n ",(t+j-1)->Tonggiatien);
	printf("HET.\n ");
}
void Menu(){
	printf("\n ");
	printf("1.Tao Link list\n ");
	printf("2. Xuat Menu\n ");
	printf("3. Them mon\n ");
	printf("4. So Ban cua quan \n ");
	printf("5. Chon Ban\n ");
	printf("6. Chon mon\n ");
	printf("7. Xuat list cuoi cung va tong tien\n ");
	printf("8. Thoat chuong trinh\n ");
	printf("9. In menu\n ");
}
int CheckSo(char *a){
	for(int i=0;i<strlen(a);i++){
		if(*(a+i)>='0' &&*(a+i)<='0'){
			return 1;
		}
	}
	return 0;
}

int CheckChuInThuong(char *a){
	for(int i=0;i<strlen(a);i++){
		if(*(a+i)>='a' && *(a+i)<='z'){
			return 1;
		}
	}
	return 0;
}

int CheckChuInHoa(char *a){
	for(int i=0;i<strlen(a);i++){
		if(*(a+i)>='A' && *(a+i)<='z'){
			return 1;
		}
	}
	return 0;
}

int CheckKhoangTrong(char *a){
	for(int i=0;i<strlen(a);i++){
		if(*(a+i)==' '){
			return 0;
		}
	}
	return 1;
}

int CheckMatKhauNhap (char *a){
	if(strlen(a)<8){
		return 0;
	}else if(CheckSo(a)==0){
		return 0;
	}else if(CheckChuInHoa(a)==0){
		return 0;
	}else if (CheckChuInThuong(a)==0){
		return 0;
	}else if(CheckKhoangTrong(a)==0){
		return 0;
	}else {
		return 1;
	}
}

void CheckImputMatKhau(char *a,int n){
	if(strlen(a)==n){
		if(a[strlen(a)-1]!='\n'){
			printf("TranBoNho\n ");
			a[strlen(a)-1]='\0';
			printf("chuoi nhap: %s",a);
			fflush(stdin);
		}else{
			a[strlen(a)-1]='\0';
		}
	}else{
		a[strlen(a)-1]='\0';
	}
}

void NhapMatKhauMoi(){
	fflush(stdin);
	while(1){
		char a[25];
		do{
			printf("Nhap mat khau moi: ");
			fgets(a,25,stdin);
			CheckImputMatKhau(a,24);
		}while(CheckMatKhauNhap(a)==0);
		char b[25];
		printf("Xac nhan mat khau: ");
		fgets(b,25,stdin);
		CheckImputMatKhau(b,24);
		if(stricmp(b,a)==0){
			FILE *fvb;
			printf("Cap nhat mat khau hoan thanh.\n ");
			//Viet ham ghi ra file
			fvb=fopen("Tai Khoan Chu Quan.text","w");
			if(fvb==NULL){
				printf("Mo tep that bai.\n ");
			}else{
				fprintf(fvb,"%s\n",a);
			}
			fclose(fvb);
			break;
		}
	}
}

int DocMatKhauTuFile(char *a){
	FILE *fvb;
	fvb=fopen("Tai Khoan Chu Quan.text","r");
	if(fvb==NULL){
		return 0;
	}else{
		fgets(a,25,fvb);
		fclose(fvb);
		printf("mk %s",a);
		return 1;
	}
}

int DangNhap(){
	char b[25];
	if(DocMatKhauTuFile(b)==0){
		return 1;
	}
	int n=0;
	while(n<=7){
		char a[25];
		printf("Nhap mat khau: ( Con %d lan nhap )\n ",7-n);
		fgets(a,25,stdin);
		printf("%d va %d \n",strlen(a) ,strlen(b));
		if(stricmp(a,b)==0){
			return 1;
		}else{
			n++;
		}
	}
	return 0;
}

void MenuChuQuan(){
	printf("1.Tao Thuc Don moi\n ");
	printf("2. Xuat menu ra man hinh\n ");
	printf("3. Bo sung danh sach\n ");
	printf("4. So Ban\n ");
	printf("5. Xap sep theo Price\n ");
	printf("6. Xap Sep theo STT\n ");
	printf("7. Xap Sep theo Name\n ");
	printf("8. Chinh Sua Xuat File\n ");
	printf("9. Xuat File menu\n ");
	printf("10. Doc File Menu\n ");
	printf("11. Nhap Mat khau moi\n ");
	printf("12. Hien Menu tuy chon\n ");
	printf("13. Thoat khoi vai tro chu quan\n ");
}

void MenuKhach(){
	printf("1. Xem Menu.\n ");
	printf("2. Chon ban.\n ");
	printf("3. Chon mon.\n ");
	printf("4. Chot goi mon.\n ");
	printf("5. Thoat khoi vai tro khach\n ");
}

void dangnhapMenu(){
	printf("1. Dang nhap voi tu cach Chu quan.\n ");
	printf("2. Dang nhap voi tu cach khach hang.\n ");
	printf("3. Thoat\n ");
}
int main(){
	int n,m;
	n=0;
	m=0; 
	dangnhapMenu();
	int choice;
	Food *f;
	f=NULL;
	f=DocMenuTuFile(&n);
	if(f==NULL){
		printf("Chua co thuc don cho quan.\n ");
	}else{
		printf("Da co thuc don cho quan\n ");
	}
	m=DocSoBan(&m);
	if(m==0){
		printf("Chua co du lieu so ban.\n ");
	}else{
		printf("Da co du lieu so ban.\n ");
	}
	Table T[m+1],*t;
	t=T;
	int j;
	int Max;
	do{
	do{
		scanf("%d",&choice);
		fflush(stdin);
	}while(choice<1||choice>3);
	switch (choice){
		case 1:{
			if(DangNhap()==1){
			printf("Thanh Cong\n ");
			}else{
				printf("That Bai\n ");
				goto Nhan;
			}
			f=DocMenuTuFile(&n);
			if(f==NULL){
				printf("Chua co thuc don cho quan.\n ");
			}else{
				printf("Da co thuc don cho quan\n ");
			}
			m=DocSoBan(&m);
			if(m==0){
				printf("Chua co du lieu so ban.\n ");
			}else{
				printf("Da co du lieu so ban.\n ");
			}
			MenuChuQuan();
			do{
			do{
				scanf("%d",&choice);
				fflush(stdin);
			}while(choice<1||choice>13);
			switch(choice){
				case 1:{//Tao thuc son moi
					ListFood(&f,&n);
					break;
				}
				case 2:{//Xuat me nu ra man hinh
					XuatMenuFood(f);
					if(f==NULL){
						printf("Chua co thuc don san\n Vui long tao (Nhan 1)\n ");
					}
					break;
				}
				case 3:{//Bo sung danh sach
					ThemCuoi(&f,&n);
					break;
				}
				case 4:{
					if(DocSoBan(&m)==0){
						printf("Chua nhap\n ");
					}else{
						printf("So Ban: %d\n ",m);
					}
					printf("Chinh sua so ban cua quan: Yes(1) or No(2)\n");
					do{
						scanf("%d",&choice);
						fflush(stdin);
					}while(choice<1 ||choice >2);
					if(choice==1){
						SoBan(&m);
					}
					Table T[m+1],*t;
					t=T;
					break;
				}
				case 5:{
					XapSepTheoPrice(f);
					break;
				}
				case 6:{
					XapSepTheoSTT(f);
					break;
				}
				case 7:{
					XapSepTheoName(f);
					break;
				}
				case 8:{
					ChinhSua(&f,&n);
					break;
				}
				case 9:{//Xuat File Menu;
					XuatFile(f,n);
					break;
				}
				case 10:{//Cap nhat lai me nu 
					f=DocMenuTuFile(&n);
					break;
				}
				case 11:{
					NhapMatKhauMoi();
					break;
				}
				case 12:{
					MenuChuQuan();
					break;
				}
				case 13:{
					printf("Thoat khoi vai tro chu quan\n ");
					choice=13;
					break;
				}
			}
			}while(choice!=13);
			break;
		}
		case 2:{
			MenuKhach();
			do{
			do{
				scanf("%d",&choice);
				fflush(stdin);
			}while(choice<1||choice>5);
			switch (choice){
				case 1:{
					XuatMenuFood();
					break;
				}
				case 2:{
					if(m==0){
						printf("Khong co so ban de chon\n ");
						choice= 4;
					}else{
						j=ChonBan(m);
					}
					break;
				}
				case 3:{
					if(j==0){
						printf("Vui long chon ban truoc khi chon mon an\n ");
						choice=5;
					}else{
						Max=ChonMon(t,j,f);
						printf("Mon an %d",Max+1);
						ChotTien(Max,t,j,f);
					}
				
					break;
				}
				case 4:{
					if(Max==0){
						printf("Vui long chon mon\n ");
						printf("Nhap 6: \n ");
					}else{
						ListChot(Max,t,j,f);
					}
					break;
				}
				case 5:{
					printf("Thoat voi vai tro la khach\n ");
					choice=4;
					break;
				}
			}
		}while(choice!=5);
			break;
		}
		case 3:{
			printf("Thoat chuong trinh\n ");
			break;
		}
	}
}while(choice!=3);
	Nhan:
		printf("Ket thuc lam viec\n ");
}

