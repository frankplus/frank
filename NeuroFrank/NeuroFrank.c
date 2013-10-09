/*
  Name: NeuroFrank
  Author: Pnb2Frank
  date of publication: 24/06/12 20.24
  Description: Una rete neurale artificiale associativa...
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define _PRECISION int

typedef struct type_neuron Tneuron;
typedef struct type_layer Tlayer;

struct type_neuron
{
    _PRECISION input_value;
    _PRECISION output_value;
};

struct type_layer
{
    Tneuron *elements;
    int num_elements;
};

/* PROTOTIPI DELLE FUNZIONI */
Tlayer BuildLayer(int Nelements);
void LoadValori(Tlayer *layer, char filename[]);
void esecuzione(Tlayer *LayerIn, Tlayer *LayerOut);
void apprendimento(Tlayer *LayerIn, Tlayer *LayerOut);
void init_layer(Tlayer *layer);
void BuildMatrice(int n, int m);
void errore(int n);

/* DICHIARO L'ARRAY BIDIMENSIONALE DEI PESI 
(l'allocazione verrà svolto dinamicamente successivamente 
quando si conosceranno le dimensioni della rete neurale) */
_PRECISION **pesi;

/* INIZIO FUNZIONE PRINCIPALE MAIN */
int main()
{
    /* DICHIARO LE VARIABILI*/
    int 
    temp,
    i,
    j,
    pesi_inizializzati = 0, 
    uscita = 0,
    size_settati = 0,
    pxl_oriz_inimg,
    pxl_vert_inimg,
    pxl_oriz_outimg,
    pxl_vert_outimg,
    NeuroniInput,
    NeuroniOutput;
    FILE *FilePtr;
    char filename[250];
    Tlayer LayerIn, LayerOut;
    
    /* CICLO ITERATIVO CHE SI CONCLUDE QUANDO VIENE RICHIESTO DALL'UTENTE */
    while(!uscita)
    {
        /* VISUALIZZO IL MENU */
        system("CLS");
        puts("1) SET DIMENSIONE IMMAGINI E GENERA RETE NEURALE");
        puts("2) APPRENDIMENTO");
        puts("3) ESECUZIONE");
        puts("4) CARICA PESI DA FILE");
        puts("5) SALVA PESI SU FILE");
        puts("6) TERMINA");
        printf("\t Scelta: ");
        
        /* SWITCH CHE ESEGUE L'OPZIONE SCELTA DALL'UTENTE */
        switch(getche())
        {
            case '1':
                if(size_settati)
                {
                    errore(5);
                    break;
                }
                /* RICEVO LE DIMENSIONI DELLE IMMAGINI CHE CORRISPONDE ALLE DIMENSIONI DELLA RETE NEURALE */
                system("CLS");
                printf("pixel orizzontali dell'immagine input: ");
                scanf("%d", &pxl_oriz_inimg);
                printf("pixel verticali dell'immagine input: ");
                scanf("%d", &pxl_vert_inimg);
                printf("pixel orizzontali dell'immagine output: ");
                scanf("%d", &pxl_oriz_outimg);
                printf("pixel verticali dell'immagine output: ");
                scanf("%d", &pxl_vert_outimg);
                
                NeuroniInput = pxl_oriz_inimg * pxl_vert_inimg;
                NeuroniOutput = pxl_oriz_outimg * pxl_vert_outimg;
                
                /* GENERO GLI STRATI DI INPUT E OUTPUT DELLE DIMENSIONI DATE */
                LayerIn = BuildLayer(NeuroniInput);
                LayerOut = BuildLayer(NeuroniOutput);
                
                /* INIZIALIZZO GLI STRATI */
                init_layer(&LayerIn);
                init_layer(&LayerOut);
                
                /* GENERO LA MATRICE DEI PESI (allocazione dinamica) */
                BuildMatrice(NeuroniInput, NeuroniOutput);
                
                size_settati = 1;
                
                break;
            case '2':
                if(!size_settati)
                {
                    errore(1);
                    break;
                }
                
                /* RICEVO I NOMI DELLE IMMAGINI */
                printf("\n\nInserire filename input: ");
                scanf("%s", filename);
                LoadValori(&LayerIn, filename);
                
                printf("\n\nInserire filename output: ");
                scanf("%s", filename);
                LoadValori(&LayerOut, filename);
                
                /* ESEGUO LA FASE DI APPRENDIMENTO */
                apprendimento(&LayerIn, &LayerOut);
                
                pesi_inizializzati = 1;
                break;
            case '3':
                if(!pesi_inizializzati)
                {
                    errore(2);
                    break;
                }
                if(!size_settati)
                {
                    errore(1);
                    break;
                }
                /* RICEVO FILENAME DI INPUT */
                printf("\n\nInserire filename input: ");
                scanf("%s", filename);
                
                /* INIZIALIZZO GLI STRATI */
                init_layer(&LayerIn);
                init_layer(&LayerOut);
                
                /* CARICO I VALORI DI INPUT */
                LoadValori(&LayerIn, filename);
                
                /* ESEGUO LA FASE DI ESECUZIONE, GENERO I VALORI DI OUTPUT */
                esecuzione(&LayerIn, &LayerOut);
                
                /* VISUALIZZO I VALORI DI OUTPUT */
                for(j=0; j<LayerOut.num_elements; j++)
                {
                    temp = LayerOut.elements[j].output_value;
                    if(j%pxl_oriz_outimg == 0) putchar('\n');
                    if(temp == -1)  putchar('.');
                    if(temp == 1)   putchar('*');
                }
                
                /* CONCLUDO FASE DI ESECUZIONE */
                printf("\n\nPremere un tasto per continuare...");
                getch();
                break;
            case '4':
                /* CARICAMENTO DEI PESI */
                if(!size_settati)
                {
                    errore(1);
                    break;
                }
                
                FilePtr = fopen("pesi.sav", "rb");
                if(!FilePtr)
                {
                    errore(4);
                    break;
                }
                for(i=0; i<LayerIn.num_elements; i++)
                    fread(pesi[i], sizeof(_PRECISION), LayerOut.num_elements, FilePtr);
                fclose(FilePtr);
                
                pesi_inizializzati = 1;
                break;
            case '5':
                /* SALVATAGGIO DEI PESI */
                if(!pesi_inizializzati)
                {
                    errore(2);
                    break;
                }
                if(!size_settati)
                {
                    errore(1);
                    break;
                }
                FilePtr = fopen("pesi.sav", "wb");
                if(!FilePtr)
                {
                    errore(4);
                    break;
                }
                for(i=0; i<LayerIn.num_elements; i++)
                    fwrite(pesi[i], sizeof(_PRECISION), LayerOut.num_elements, FilePtr);
                fclose(FilePtr);
                break;
            case '6':
                uscita = 1;
        }
    }
    return 0;
}

/* FUNZIONE DI GENERAZIONE DI UNO STRATO */
Tlayer BuildLayer(int Nelements)
{
    Tlayer layer; //dichiaro struttura layer
    layer.elements = malloc(Nelements * sizeof(Tneuron)); //alloco dinamicamente i neironi dello strato
    layer.num_elements = Nelements; //indico quanti neuroni sono presenti nello strato
    return layer; //ritorno layer
}

/* FUNZIONE DI ALLOCAZIONE DELLA MATRICE DEI PESI (approccio array di array)*/
void BuildMatrice(int n, int m)
{
    int i, j;
    
    pesi = (_PRECISION**) malloc(n * sizeof(_PRECISION*));
    
    if(!pesi)
    {
        errore(3);
        exit(0);
    }
    
    for(i=0; i<n; i++)
    {
        pesi[i] = (_PRECISION*) malloc(m * sizeof(_PRECISION));
        if(!pesi[i])
            {
                errore(3);
                exit(0);
            }
    }
    
    /* INIZIALIZZO LA MATRICE PESI */
    for(i=0; i<n; i++)
        for(j=0; j<m; j++)
            pesi[i][j] = 0;
}

/* FUNZIONE DI CARICAMENTO DEI VALORI IN UNO STRATO DATO IL FILENAME */
void LoadValori(Tlayer *layer, char filename[])
{
    char ch, i=0;
    FILE *FilePtr;
    FilePtr = fopen(filename, "r");
    
    /* CONTROLLO SE CI SONO ERRORI */
    if(!FilePtr)
    {
        errore(4);
        exit(0);
    }
    
    /* CARICO I VALORI */
    while(!feof(FilePtr) && i<layer->num_elements)
    {
        ch = fgetc(FilePtr);
        switch(ch)
        {
            case '.':
                layer->elements[i].output_value = -1;
                i++;
                break;
            case '*':
                layer->elements[i].output_value = 1;
                i++;
                break;
        }
    }
    fclose(FilePtr);
    return;
}

/* FUNZIONE DI ESECUZIONE,  */
void esecuzione(Tlayer *LayerIn, Tlayer *LayerOut)
{
    int i, j, stabilita=0;
    while(!stabilita)
    {
        stabilita = 1;
        
        // DALL' INPUT VERSO L'OUTPUT:
        for(j=0; j<LayerOut->num_elements; j++) //per ogni neurone di output
        {
            LayerOut->elements[j].input_value = 0; //inizializzo proprio il valore di input
            
            for(i=0; i<LayerIn->num_elements; i++) //per ogni neurone di input
                LayerOut->elements[j].input_value += LayerIn->elements[i].output_value * pesi[i][j];
            
            //FUNZIONE DI TRASFERIMENTO
            if(LayerOut->elements[j].input_value>=0)
                LayerOut->elements[j].output_value=1;
            else
                LayerOut->elements[j].output_value=-1;
        }
        
        // DALL'OUTPUT VERSO L'INPUT(RETROAZIONE):
        for(i=0; i<LayerIn->num_elements; i++)
        {
            LayerIn->elements[i].input_value = 0;
            
            for(j=0; j<LayerOut->num_elements; j++)
                LayerIn->elements[i].input_value += LayerOut->elements[j].output_value * pesi[i][j];
                
            //FUNZIONE DI TRASFERIMENTO CON VERIFICA DELLA STABILITA'
            if(LayerIn->elements[i].input_value>=0)
            {
                if(LayerIn->elements[i].output_value == -1) //se c'è una variazione del valore di output
                    stabilita = 0; // stabilità=0, si ripete il ciclo while
                LayerIn->elements[i].output_value=1;
            }
            else
            {
                if(LayerIn->elements[i].output_value == 1) //se c'è una variazione del valore di output
                    stabilita = 0; // stabilità=0, si ripete il ciclo while
                LayerIn->elements[i].output_value=-1;
            }
        }
    }
}

/* FUNZIONE DI APPRENDIMENTO */
void apprendimento(Tlayer *LayerIn, Tlayer *LayerOut)
{
    int i, j;
    
    for(i=0; i<LayerIn->num_elements; i++)
        for(j=0; j<LayerOut->num_elements; j++)
            pesi[i][j] += (LayerIn->elements[i].output_value) * (LayerOut->elements[j].output_value);
}

/* FUNZIONE DI INIZIALIZZAZIONE DEI VALORI DI INPUT E OUTPUT DI OGNI NEURONE DELLO STRATO DATO */
void init_layer(Tlayer *layer)
{
    int i;
           
    for(i=0; i<layer->num_elements; i++)
    {
        layer->elements[i].input_value = 0;
        layer->elements[i].output_value = 0;
    }
}

/* FUNZIONE DI VISUALIZZAZIONE DELL'ERRORE */
void errore(int n)
{
    printf("\n\n\tERROR: %d\n", n);
    switch(n)
    {
        case 1:
            puts("Imposta dimensioni immagini.");
            break;
        case 2:
            puts("Pesi non inizializzati!");
            puts("Eseguire l'apprendimento. ");
            break;
        case 3:
            puts("Non c'e' abbastanza memoria.");
            break;
        case 4:
            puts("Errore nell'apertura del file,");
            puts("Probabilmente il file e' inesistente.");
            break;
        case 5:
            puts("Dimensioni gia' settati.");
            break;
        default:
            puts("Codice errore sconosciuto.");
    }
    
    printf("Premere un tasto per continuare... ");
    getch();
}
