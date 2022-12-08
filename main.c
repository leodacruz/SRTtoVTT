#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>		// Para usar strings

#ifdef WIN32
#include <windows.h>    // Apenas para Windows
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>     // Funções da OpenGL
#include <GL/glu.h>    // Funções da GLU
#include <GL/glut.h>   // Funções da FreeGLUT
#endif

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

// Um pixel Pixel (24 bits)
typedef struct {
    unsigned char r, g, b;
} Pixel;

// Uma imagem Pixel
typedef struct {
    int width, height;
    Pixel* img;
} Img;




// Protótipos
void load(char* name, Img* pic);
void valida();
 void corPrinc(int corR, int corG, int corB,int* rgb);
// Funções da interface gráfica e OpenGL
void init();
void draw();
void keyboard(unsigned char key, int x, int y);

// Largura e altura da janela
int width, height;

// Identificadores de textura
GLuint tex[2];

// As 2 imagens
Img pic[2];

// Imagem selecionada (0,1)
int sel;

// Carrega uma imagem para a struct Img
void load(char* name, Img* pic)
{
    int chan;
    pic->img = (Pixel*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

  /*
    Função para determinar qual a cor predominante  
    0=r 1=g 2=b
    */
void corPrinc(int corR, int corG, int corB,int* rgb){
        int aux=corG;
        if(aux<corB){
            aux=corB;
        }
        if(aux<corR){
            aux=corR;
        }

        if(aux==corG){*rgb= 1; }else{
              if(aux==corR) {*rgb= 0; } else{
                  if(aux==corB){*rgb= 2; }    
              }
        }      
    }

int main(int argc, char** argv)
{
    if(argc < 1) {
        printf("artistic [im. entrada]\n");
        exit(1);
    }
	glutInit(&argc,argv);

	// Define do modo de operacao da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// pic[0] -> imagem de entrada
	// pic[1] -> imagem de saida

	// Carrega a imagem
    load(argv[1], &pic[0]);

    width = pic[0].width;
    height = pic[0].height;

    // A largura e altura da imagem de saída são iguais às da imagem de entrada (0)
    pic[1].width  = pic[0].width;
    pic[1].height = pic[0].height;
	pic[1].img = calloc(pic[1].width * pic[1].height, 3); // W x H x 3 bytes (Pixel)

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(width, height);

	// Cria a janela passando como argumento o titulo da mesma
	glutCreateWindow("Arte Computacional");

	// Registra a funcao callback de redesenho da janela de visualizacao
	glutDisplayFunc(draw);

	// Registra a funcao callback para tratamento das teclas ASCII
	glutKeyboardFunc (keyboard);

    // Exibe as dimensões na tela, para conferência
    printf("Origem  : %s %d x %d\n", argv[1], pic[0].width, pic[0].height);
    sel = 0; // entrada

	// Define a janela de visualizacao 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,width,height,0.0);
	glMatrixMode(GL_MODELVIEW);

    // Converte para interpretar como matriz
    Pixel (*in)[width] = (Pixel(*)[width]) pic[0].img;
    Pixel (*out)[width] = (Pixel(*)[width]) pic[1].img;










  //===========================================================================================================================================PROGRAMA TRABALHO 1 



   /*
   
   Escolha semente = pega a imagem original e divide em quadrados, após, se percorre o quadrado e se faz a escolha de um pixel, esse
   pixel é a semente. O numero de sementes é igual a de quadrados.
   Para escolher o numero de sementes só são validos numeros que dividam 800 e 600 sem gerar numeros quebrados. Os validos são:
   20 = 400 sementes; 50 = 2500 sementes; 100 = 10.000 sementes ; 200 = 40.000 sementes.
   As sementes são guardadas em uma matriz, que só salva a posição x e y, que é a posição da semente na imagem original.

   Preenchimento dos pixel= Como a imagem foi divida em quadrados, cada um deles foi preenchido com a cor da semente presente nele.Bem simples.

   Refinamento= tira um pouco da pixelização da imagem, fazendo contornos melhores
   */


   //                           ******************************   Escolha das sementes **********************************




   int semente =200;                          //escolha da qtd de sementes
   int larg=width/semente;                    //limite do tamanho do quadrado, largura
   int alt=height/semente;                    //limite do tamanho do quadrado, altura
   int pixelAux [2];                          //x e y
   int sementes [semente*semente+1][2];       //matriz das sementes, +1 para o refinamento
   int cont1=0;                               //contador para aux na hora que guardar o "x" e "y" na matriz
   
       for(int y=0; y<height; y+=alt){              //posiciona o "y" no início dos quadrados
          for(int x=0; x<width; x+=larg) {          //posiciona o "x" no início dos quadrados
              pixelAux[0]=y;                        //inicializa o vetor auxiliar com a posição do "y" do primeiro pixel do quadrado
              pixelAux[1]=x;                        //inicializa o vetor auxiliar com a posição do "x" do primeiro pixel do quadrado

              for(int a=y;a< y+alt;a++){                        //percorre dentro do quadrado cada linha do y
                  for (int b = x; b < x+larg; b++){             //percorre dentro do quadrado cada coluna do x


                      /*Escolha da semente
                      
                      Aqui está se percorrendo por todos os pixels de um quadrado. A escolha do pixel se da por tres ifs, primeiro 
                      prioriza-se a escolha de um 
                      pixel verde, depois, caso não exista, é escolhido um vermelho e depois o azul. A escolha do verde primeiro se da 
                      pelo fato de nós humanos enxergamos
                      muito tons de verde, assim, quanto mais verde na imagem, menor sera a diferença entre a original e a estilizada.
                      O vermelho logo em seguida pelo mesmo fator, e o azul por último.
                      
                      Os ifs funcionam do mesmo modo, só trocando a cor. Pergunta-se se no pixel atual o verde é maior do que do vetor
                      auxlizar (salva a pos de um pixel), caso for maior, ele pergunta se o vermelho e azul são inferiores a esse
                      verde,se for, salva esse pixel no vetor aux. E todos os demais ifs funcionam deste mesmo modo.

                     Caso ele passe por todo o quadrado e o valor que está dentro do vetor auxiliar for o mesmo que existia antes, ele 
                     pega o pixel mais centralizado do quadrado. Isso significa que esse quadrado possivellmente é composto por uma só 
                     cor.
                      */
                      if ((in[a][b].g > in[pixelAux[0]][pixelAux[1]].g) && 
                         (in[a][b].g > 105 && in[a][b].r < 35 && in[a][b].b < 35)) { 
                          pixelAux[0] = a;
                          pixelAux[1] = b;
                      }
                      else
                      { if ((in[a][b].r > in[pixelAux[0]][pixelAux[1]].r) &&
                           (in[a][b].r > 105 && in[a][b].g < 35 && in[a][b].b < 35)){
                              pixelAux[0] = a;
                              pixelAux[1] = b;
                          }
                          else
                          { if ((in[a][b].b > in[pixelAux[0]][pixelAux[1]].b) &&
                                (in[a][b].b > 105 && in[a][b].g < 35 && in[a][b].r < 35)){
                                  pixelAux[0] = a;
                                  pixelAux[1] = b;
                              }
                          }
                      } 
                  }
              }


              if(pixelAux[0]==y && pixelAux[1]==x){    //caso ele passou pelo quadrado e não escolheu um pixel, pega o centralizado
                sementes[cont1][0]=  y+(alt/2);
                sementes[cont1][1]=  x+(larg/2);   
              } else{
                    sementes[cont1][0]= pixelAux[0];
                    sementes[cont1][1]=  pixelAux[1];   
              }
             cont1++;
          }           
       }





   //                           ******************************   Escolha das cores dos pixels **********************************





   /* Se percorre novante os quadrados só que agora o quadrado vai ser preenchido da cor da semente que está naquele quadrado
   */
       cont1=0;
       for(int y=0; y<height; y+=alt){                              //posiciona o "y" sempre no inicio dos quadrados
          for(int x=0; x<width; x+=larg) {                          //posiciona o "x" sempre no inicio dos quadrados
              int altLimite= y+alt;
              int largLimite= x+larg;
              
              for(int a=y;a< altLimite;a++){                        //percorre dentro do quadrado cada linha do y
                  for(int b=x;b< largLimite;b++){                   //percorre dentro do quadrado cada coluna do x
               out[a][b].r = in[sementes[cont1][0]][sementes[cont1][1]].r;  
               out[a][b].g = in[sementes[cont1][0]][sementes[cont1][1]].g;  
               out[a][b].b = in[sementes[cont1][0]][sementes[cont1][1]].b;     
              }
              }
              cont1++;  
          }           
       }





        //                           ******************************   Refinamento dos pixels 1  **********************************




        /*
        Melhora os cantos para parecerem menos pixelizados. Na imagem original existe partes que possuem o contorno assim: /.
        Na imagem de saída isso fica feio pq está pixelizado, assim, essa parte suaviliza isso, igual o Anti-Aliasing só
        que aplicado somente para formas assim: / ou \ . Olhe para o teto do predio antes e depois de ativar esse refinamento. No 
        programa abaixo está escrito uma parte que caso descomentada ele desativa o refinamento. 
        Fica mais perceptivel quanto menos sementes usar
        */
       

       cont1=0;
       for(int y=0; y<height; y+=alt){                  //posiciona o "y" sempre no inicio dos quadrados
          for(int x=0; x<width; x+=larg) {              //posiciona o "x" sempre no inicio dos quadrados

              int direita=0;                // controle limite do quadrado a direita
              int esquerda=0;               // controle limite do quadrado a esquerda
              int debaixo=0;                // controle limite do quadrado a abaixo
              int libera=0;                 // libera fazer o refinamento, caso 1 faz com o / e 2 \

              if((x+larg)<800){      //não deixa prosseguir caso esteja no quadrado mais ao canto direito         
                 }else{
                  direita=1;
                    }
              if((x-larg)>0){       //não deixa prosseguir caso esteja no quadrado mais ao canto esquerdo           
                 }else{
                  esquerda=1;
                    }
              if((y+alt)<600){    //não deixa prosseguir caso esteja no quadrado da ultima linha           
                 }else{
                  debaixo=1;
                  }

                  
 

             // **********************    DESATIVAR REFINAMENTO ********************************
                  // direita=1; //caso queira testar sem o refinamento DESCOMENTE


              if(direita==0 && debaixo==0 && esquerda==0  ){// condição para fazer o refinamneto
                  /* A condição para realizar o refinaento é se o quadrado do seu lado e o abaixo são de cores diferentes da tua. Ai ele
                  interpreta que está ocorrendo este formato "/" ou este "\".
                  Abaixo está perguntando a cor principal de cada quadrado,essa cor é definida pela que tem a maior valor no r,g ou b.
                  */
                  

                  // *** valor das sementes dentro dos quadradoS ***

                  //cor principal de cada quadrado; rgb1=vc; rgb2=sua direita; rgb3=abaixo; rgb4=sua esquerda
                  int rgb1= -1;
                  int rgb2= -1;
                  int rgb3=-1;// 0=r 1=g 2=b
                  int rgb4=-1;// 0=r 1=g 2=b

                  // Quadrado do meio; voce
                  int vcR=in[sementes[cont1][0]][sementes[cont1][1]].r;  // valor do r
                  int vcG=in[sementes[cont1][0]][sementes[cont1][1]].g;  // valor do g
                  int vcB=in[sementes[cont1][0]][sementes[cont1][1]].b;  // valor do b

                  // Quadrado da direita; 
                  int dirR=in[sementes[cont1][0]][sementes[cont1][1]+larg].r;  // valor do r
                  int dirG=in[sementes[cont1][0]][sementes[cont1][1]+larg].g;  // valor do g
                  int dirB=in[sementes[cont1][0]][sementes[cont1][1]+larg].b;  // valor do b

                  // Quadrado da esquerda;
                  int esqR=in[sementes[cont1][0]][sementes[cont1][1]-larg].r;  // valor do r
                  int esqG=in[sementes[cont1][0]][sementes[cont1][1]-larg].g;  // valor do g
                  int esqB=in[sementes[cont1][0]][sementes[cont1][1]-larg].b;  // valor do b

                  // Quadrado debaixo; 
                  int baiR=in[sementes[cont1][0]+alt][sementes[cont1][1]].r;  // valor do r
                  int baiG=in[sementes[cont1][0]+alt][sementes[cont1][1]].g;  // valor do g
                  int baiB=in[sementes[cont1][0]+alt][sementes[cont1][1]].b;  // valor do b

                  
                 /*é feita a chamada para a função que ira fazer o calculo da cor principal;
                  a função está na linha 75
                 */
                  corPrinc(vcR,vcG,vcB,&rgb1);// 0=r 1=g 2=b
                  corPrinc(dirR,dirG,dirB,&rgb2);// 0=r 1=g 2=b
                  corPrinc(esqR,esqG,esqB,&rgb4);// 0=r 1=g 2=b
                  corPrinc(baiR,baiG,baiB,&rgb3);// 0=r 1=g 2=b
                  

               /*libera 1 caso requesite a condição de fazer esse refinamento /, que eh quando os quadrados abaixo e a direita são de cores diferentes da
               tua e eles sejam da mesma cor
               libera 2 é o mesmo só que fazendo com o quadrado da esquerda
               */   
               if( (rgb1!=rgb2 && rgb1!=rgb3) && (rgb2==rgb3)){ 
                   libera=1;
               } else{
                  if( (rgb1!=rgb4 && rgb1!=rgb3) && (rgb4==rgb3)){
                  libera=2;
                  } 
               }
              }



          /*Aqui faz o refinamento do quadrado. antes e depois de passar pelo libera 1
          -----------          --------------
          |         |          | cor     /  |
          |Cor verde|  ----->  |verde /     |
          |         |          | / cor verm |
          -----------          --------------
          Ele divide o quadrado e coloca a cor em um lado e no ele
          coloca a cor da semente do quadrado do lado
          No caso do libera 2 é igual so que o corte no quadrado e nesse sentindo oposto \
          */
          if(libera==1){
              int altLimite= y+alt;
              int largLimite= x+larg;
              int triangulo=largLimite;
              for(int a=y;a< altLimite;a++){// percorre dentro do limite de y
              

                  for(int b=x;b< triangulo;b++){ 
                 out[a][b].r = in[sementes[cont1][0]][sementes[cont1][1]].r;  
                 out[a][b].g = in[sementes[cont1][0]][sementes[cont1][1]].g;  
                 out[a][b].b = in[sementes[cont1][0]][sementes[cont1][1]].b;   
                  }
                  for(int b=triangulo;b< largLimite;b++){

                 out[a][b].r = in[sementes[cont1+1][0]][sementes[cont1+1][1]].r;  
                 out[a][b].g = in[sementes[cont1+1][0]][sementes[cont1+1][1]].g;  
                 out[a][b].b = in[sementes[cont1+1][0]][sementes[cont1+1][1]].b;                
                  }
                  triangulo--;
              }
          }

          if(libera==2){
              int altLimite= y+alt;
              int largLimite= x+larg;
              int triangulo=x;
              for(int a=y;a< altLimite;a++){
                  for(int b=triangulo;b< largLimite;b++){ 
                 out[a][b].r = in[sementes[cont1][0]][sementes[cont1][1]].r;  
                 out[a][b].g = in[sementes[cont1][0]][sementes[cont1][1]].g;  
                 out[a][b].b = in[sementes[cont1][0]][sementes[cont1][1]].b; 
               
                  }
                  for(int b=x;b< triangulo;b++){
               out[a][b].r = in[sementes[cont1+1][0]][sementes[cont1-1][1]].r;  
               out[a][b].g = in[sementes[cont1+1][0]][sementes[cont1-1][1]].g;  
               out[a][b].b = in[sementes[cont1+1][0]][sementes[cont1-1][1]].b;                
                  }
               triangulo++;
              }
          }
              cont1++; 
          }           
       }

    
     //==============================================================================================================================================FIM PROGRAMA TRABALHO 1 


    






	// Cria texturas em memória a partir dos pixels das imagens
    tex[0] = SOIL_create_OGL_texture((unsigned char*) pic[0].img, width, height, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
    tex[1] = SOIL_create_OGL_texture((unsigned char*) pic[1].img, width, height, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

	// Entra no loop de eventos, não retorna
    glutMainLoop();
}

// Gerencia eventos de teclado
void keyboard(unsigned char key, int x, int y)
{
    if(key==27) {
      // ESC: libera memória e finaliza
      free(pic[0].img);
      free(pic[1].img);
      exit(1);
    }
    if(key >= '1' && key <= '2')
        // 1-2: seleciona a imagem correspondente (origem ou destino)
        sel = key - '1';
    glutPostRedisplay();
}

// Callback de redesenho da tela
void draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Preto
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Para outras cores, veja exemplos em /etc/X11/Pixel.txt

    glColor3ub(255, 255, 255);  // branco

    // Ativa a textura corresponde à imagem desejada
    glBindTexture(GL_TEXTURE_2D, tex[sel]);
    // E desenha um retângulo que ocupa toda a tela
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    glTexCoord2f(0,0);
    glVertex2f(0,0);

    glTexCoord2f(1,0);
    glVertex2f(pic[sel].width,0);

    glTexCoord2f(1,1);
    glVertex2f(pic[sel].width, pic[sel].height);

    glTexCoord2f(0,1);
    glVertex2f(0,pic[sel].height);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Exibe a imagem
    glutSwapBuffers();
}