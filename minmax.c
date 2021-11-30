#include "gobang.h"

//����������������
int ai_x,ai_y;

//�жϵ��Ƿ����ھ� ����Ч��
int hasNeighbor(Point p){
    if(num==1 || num==2){//���ֵڶ���������ֻ�Һ��ӾŹ���
        for(int i=0;i<4;i++){//4������
            for(int j=-1;j<=1;j++){//���Ҿ���1
                if(j!=0){
                    Point np=nextPoint(p,i,j);
                    if(inBoard(np) && innerBoard[np.x][np.y]==1)
                        return 1;
                }
            }
        }
    }else{//֮���������������ӵ�2��������
        for(int i=0;i<4;i++){
            for(int j=-2;j<=2;j++){//���Ҿ���2
                if(j!=0){
                    Point np=nextPoint(p,i,j);
                    if(inBoard(np) && innerBoard[np.x][np.y]!=0)
                        return 1;
                }
            }
        }
    }
    return 0;//û���ھ�
}

//����С�����������
LL minmax(int depth,LL alpha,LL beta,int player) {
    Move moves[224];
    int length=inspireFind(moves,player);//���������ӵ�
    if(length>WIDTH)
        length=WIDTH-rand()%3;//������֦ �������

    for (int i = 0; i < length; i++) {
        set(moves[i].p, player);//ģ������
        LL temp = -alphaBeta(depth - 1, -beta, -alpha,opp(player),moves[i].p);//�ݹ�
        unSet(moves[i].p);//��ԭ����
        if (temp >= beta) {
            return beta;//��֦
        }
        if (temp > alpha) {
            alpha = temp;
            ai_x = moves[i].p.x;//��¼�������
            ai_y = moves[i].p.y;
        }
    }
    return alpha;
}

//������Сֵ���� ��һ���ۺ���˫���ļ���д��
LL alphaBeta(int depth,LL alpha,LL beta,int player,Point p) {
    if (JudgeFive(p.x,p.y))//���Ӻ����
        return wholeScore(player);//���ص�ǰ�����
    if (depth == 0 || num==SIZE*SIZE) {//���Ϊ0������
        return wholeScore(player);
    }

    Move moves[224];
    int length=inspireFind(moves,player);
    if(length>WIDTH)
        length=WIDTH-rand()%3;//������֦ �������

    for (int i = 0; i < length; i++) {
        set(moves[i].p, player);//ģ������
        LL temp = -alphaBeta(depth - 1, -beta, -alpha,opp(player),moves[i].p);//ע��Ҫȡ��ֵ������alpha��beta
        unSet(moves[i].p);//��ԭ����
        if (temp >= beta) {
            return beta;//��֦
        }
        if (temp > alpha) {
            alpha = temp;
        }
    }
    return alpha;
}

//����ʽ����
int inspireFind(Move *scoreBoard,int player){
    int length=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(innerBoard[i][j]==0) {//ֻ�������ϵĿ�λ
                Point p = {i, j};

                if (hasNeighbor(p) && !forbiddenHand(p, player)) {
                    scoreBoard[length].score = singleScore(p,player);//�ҷ��ʺϽ����ĵ�
                    if(!forbiddenHand(p,opp(player))){
                        scoreBoard[length].score += singleScore(p,opp(player));//�Է���Ҫ���صĵ�
                    }
                    scoreBoard[length++].p = p;
                }
            }
        }
    }
    shellSort(scoreBoard,length);//���ݷ����������� �������Ӽ�֦Ч��
    return length;
}

//ϣ������
void shellSort(Move *s,int len){
    int i,j,gap;
    Move temp;
    for (gap=len/2;gap>0;gap/=2){
        for(i=gap;i<len;i+=1){
            for(j=i-gap;j>=0 && s[j].score<s[j+gap].score;j-=gap){
                temp = s[j+gap];
                s[j+gap]=s[j];
                s[j]=temp;
            }
        }
    }
}

//��ɱ��ȡ˫���ֿ���д�� ���ÿ����������һ���Գƺ���
//ͳһ��1��ʾ����ɱ��ɹ� 0��ʾʧ��
//��ɱ���
int killSearch(void){
    int depth=KILLDEPTH;
    Move kill[100];
    int length=findComKill(kill);//����ɱ��
    if(length==0)//û���ҵ�ɱ��
        return 0;
    if (length>9)//��ɱ��϶�ʱ�������
        depth=8;
    for (int i=0; i<length; i++){
        set(kill[i].p,id);//ģ������
        int killed=minKill(depth-1,kill[i].p);//������Ҽ�С��
        unSet(kill[i].p);//��ԭ����
        if(killed){//��ɱ�ɹ�
            ai_x=kill[i].p.x;//��¼������ӵ�
            ai_y=kill[i].p.y;
            return 1;
        }
    }
    return 0;
}

//������ɱ�����Բ�
int maxKill(int depth,Point p){
    if(JudgeFive(p.x,p.y))//������ӳ���
        return 0;
    if(depth==0)//��������δɱ��ɹ�
        return 0;

    Move kill[100];
    int length=findComKill(kill);
    if(length==0)
        return 0;
    for (int i=0;i<length; i++){
        set(kill[i].p,id);
        int killed=minKill(depth-1,kill[i].p);
        unSet(kill[i].p);
        if(killed){//����һ��ɱ��ɹ�
            return 1;
        }
    }
    return 0;
}

//��С��ɱ����Ҳ�
int minKill(int depth,Point p){
    if(JudgeFive(p.x,p.y))//�������ӳ���
        return 1;
    if(depth==0)
        return 0;

    Move kill[100];
    int length=findHumKill(kill);
    if(length==0)
        return 0;
    for (int i=0;i<length; i++){
        set(kill[i].p,opp(id));
        int killed=maxKill(depth-1,kill[i].p);
        unSet(kill[i].p);
        if(!killed){
            return 0;
        }
    }
    return 1;//���޷���ס
}

//Ѱ�ҵ��Կ����ӵ�
int findComKill(Move *move){
    int length=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(innerBoard[i][j]==0) {//ֻ����λ
                Point p = {i, j};
                if (hasNeighbor(p) && !forbiddenHand(p,id)) {
                    int score = singleScore(p,id);
                    if(score>5000){//ֻ��ɱ��
                        move[length].score=score;
                        move[length++].p = p;
                    }
                }
            }
        }
    }
    shellSort(move,length);//����
    return length;
}

//Ѱ����������ӵ�
int findHumKill(Move *move){
    int length=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(innerBoard[i][j]==0) {//ֻ����λ
                Point p = {i, j};
                if (hasNeighbor(p) && !forbiddenHand(p,opp(id))) {
                    int score = singleScore(p,opp(id));//��ҷ�ɱ�� ����
                    if(!forbiddenHand(p,id)){
                        score += singleScore(p,id);//���Է�ɱ�� ����
                    }
                    if(score>5000){
                        move[length].score=score;
                        move[length++].p = p;
                    }
                }
            }
        }
    }
    shellSort(move,length);//����
    return length;
}
