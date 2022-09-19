#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include ".\gotoxy.h" 
#include <time.h>
#define NOM_FILE "date.txt"

int validar_numero(char numero[]);
int validar_letras(char numero[]);
void actualizar();
int op,j=1,i=0;
char op1[2];
int contaUsu=1,contaPro=1;
void ingresoproductos(int idpro );
void ingresoUso (int id);
void login();
void entradas();
void salida();
void eliminar();
FILE *usuarios;
void cargar();
void cargar1();
void tienpo();
void guardarfactura();
void facturar();
void VerFactura();
void BorrarFactura();
void Cambiousu();
void Cambiocontra();
void clientesag();
void clientesmos();
void clientesDELETE();
void ayuda();

int g=0;
    char cedula[100],telefono[100],N,M;
    char clave[100],usu[100];
int l=1;

char usuario_global[30]; // nombre de la sesión actual

//Declaro variables de tipo globales 
FILE * ptr;
short z,x=14,y=24,f=0, cantcompra=0;
char clientefactura[50];
int d;

typedef struct crearUsuario{
    int id;
    int cedula;
    char nombre[20];
    char apellido[20];
    int telf;
}crearUsuario;

crearUsuario crear(int IdU);
crearUsuario informacion[100];

typedef struct productoEstructura{
    int id;
    char nomPro[100];  
    char lote[10];
    float precio;
    int cantidad;
    float total;
}productoEstructura;

productoEstructura ingresoPro(int idp);
productoEstructura bodega[100];

typedef struct clientesDat {
    char ced[30];
    char nomb[30];
    char apell[30];
    char phone[30];
}clientesDat;


//Una estructura para cada campo de la factura
struct registroVentas
{
    char nombreCliente[20];
    float cantidad;
    char nomPro[100];
    float precio;
    float total;
    float totalaPagar;
}factura[100];

int main(void)
{
    
    cargar();
    cargar1();
     while (op!=6){
        system("cls");
        printf("\n\t\t\t\t***** MENU PRINCIPAL *****");
        printf("\n\t---------------------------------------------");
        printf("\n\n\t\t1.-Crear usuario");
        printf("\n\t\t2.-Ingresar al Sistema");
        printf("\n\t\t3.-Menu Ayuda");
        printf("\n\t\t4.-Salir\n");
        printf("\n\t---------------------------------------------");
        do{
            printf("\n\t\tIngrese su eleccion: ");
            scanf("%s",op1);
            N=validar_numero(op1);
        }while(N==0);
        op=atoi(op1);
        switch(op){    
            case 1:{
                system("cls");
                printf("\n\t\t\t\t***** NUEVO USUARIO *****");
                printf("\n\t---------------------------------------------");
                informacion[l]=crear(l);
                l++;
                break;
            }
            case 2:{
                system("cls");
                printf("\n\t\t\t***** Inicio de sesion *****");
                login();
                break;
            }
            case 3:{
                system("cls");
                printf("\n\t\t\t ***** SISTEMA DE AYUDA *****\n");
                ayuda();
                system("pause");	
			    break;
		    }
            case 4:{
                system("cls");
                printf("\n\t\t\t ***** HASTA PRONTO *****");
                break;  
            }
            default:{
                printf("\n\t\t\t\t***** Opcion incorrecta *****");
                system("pause");
            }
        }
    }
    return 0;
}

 void login(){
    FILE *ingreso;
    int bencontro=0,intento=1,ac;
    char  password[100];
    char usuario[100]; 
    char lineausuario[100],lineapasword[100];
    char codUsu[100];

    int codU;
    do{

        printf("\n\t--------------------------------------------------------------");
        printf("\n\t\tIntento numero: %d",intento);
        printf("\n\t\tIngrese su nombre de usuario: ");
        scanf("%s",usuario);
        printf("\n\t\tIngrese su clave: ");
        scanf("%s",password);   
        if ((ingreso = fopen("Datos/nuevoUsu.txt","r"))==NULL){
            printf("\nEL USUARIO NO EXISTE");

        }

        while (!feof(ingreso)){ 
            fgets(codUsu,10,ingreso);
            if(fgets(lineausuario,100,ingreso)!=NULL)
            {
                if(fgets(lineapasword,100,ingreso)!=NULL)
                {
                    strcpy(codUsu,strtok(codUsu,"\n"));
                    strcpy(lineausuario,strtok(lineausuario,"\n"));
                    strcpy(lineapasword,strtok(lineapasword,"\n"));
                    if(strcmp(usuario,lineausuario)==0 && strcmp(password,lineapasword)==0){
                        codU=atoi(codUsu);
                        bencontro=-1;
                        strcpy(usuario_global, usuario);
                        break;

                    }
                }
                else{
                    printf("\nLa clave no existe");
                }
            }
            else{
                //printf("\n El usuario no existe");
            }
        }
        fclose(ingreso);
        if(bencontro){
                      
            do{
                char ac1[10];
                int ac=0;
                system("cls");
                printf("\n\t\t\t***** MENU PRINCIPAL *****");
                printf("\n\t\t\t***** BIENVENIDO %s *****", informacion[codU].nombre);
                printf("\n\t---------------------------------------------");
                printf("\n\t\t\tBIENVENIDO AL SISTEMA DE INVENTARIOS");
                printf("\n\t1.-Ingreso de Productos");
                printf("\n\t2.-Reporte de Productos");
                printf("\n\t3.-Menu Movimientos");
                printf("\n\t4.-Entradas y Salidas");
                printf("\n\t5.-Busqueda de Productos");
                printf("\n\t6.-Eliminar Producto");
                printf("\n\t7.-Mostrar usuarios");
                printf("\n\t8.-Cambio de clave");
                printf("\n\t9.-Cambio de usuario");
                printf("\n\t10.-Agregar clientes");
                printf("\n\t11.-Mostrar clientes");
                printf("\n\t12.-Eliminar clientes");
                printf("\n\t13.-Salir");
                printf("\n\t-----------------------------------------------");
                do{
                    printf("\n\tIngrese su eleccion: ");
                    scanf("%s",ac1);
                    N=validar_numero(ac1);
                }while(N==0);
                ac=atoi(ac1);
                switch(ac){
                    case 1:{
                        system("cls");
                        printf("\n\t\t\t\t***** INGRESO DE PRODUCTOS *****");
                        printf("\n\t---------------------------------------------");
                        bodega[j]=ingresoPro(j);
                        j++;
                        break;
                    }
                    case 2:{
                        float tot=0;
                        system("cls");
                        printf("\n\t\t*****PRODUCTOS EXISTENTES EN BODEGA*****");
                        printf("\n\t---------------------------------------------------------------------------------------------------------------------");
                        printf("\n\tCOD\t\t\tPRODUCTO\t\t\tLOTE\t\tSTOCK\t\tPRECIO\t\tTOTAL");
                        printf("\n\t---------------------------------------------------------------------------------------------------------------------");
                        for(i=1;i<j;i++){
                            printf("\n\t%d\t\t%s\t\t\t%s\t\t%d\t\t%.2f$\t\t%.2f$",bodega[i].id,bodega[i].nomPro,bodega[i].lote,bodega[i].cantidad,bodega[i].precio,bodega[i].total);
                            tot+=bodega[i].total;   
                        }
                        printf("\n\t---------------------------------------------------------------------------------------------------------------------");
                        printf("\n\t\t\t\t\t\t\t\t\t\tTotal en bodega: %.2f$",tot);
                        printf("\n\t---------------------------------------------------------------------------------------------------------------------");
                        printf("\n\t\tPara regresar al menu anterior presione 1 ");
                        printf("\n\t1.-SI: ");
                        int y;
                        scanf("%d",&y);
                        if(y==1){
                            break;
                        }
                        else{
                            break;  
                        }
                    }
                    case 3:{
                        int opciones;
                        char temp[10];
                        system("cls");
                        
                        printf("\n\n\t\t1- Facturar");
                        printf("\n\n\t\t2- Reporte de Facturas");
                        printf("\n\n\t\t3- Borrar factura");
                        printf("\n\n\t\t4- Salir");
                        fgets(temp,10,stdin);
                        do{
                            printf("\n\n\t\tSelecciones una opcion: ");
                            scanf("%s",temp);
                            N=validar_numero(temp);
                        }while (N==0);
                        opciones=atoi(temp);

                        if(opciones == 1)
                        {
                            facturar();
                            break;
                        }
                        else if(opciones == 2){
                            VerFactura();
                            break;
                        }
                        else if(opciones == 3){
                            BorrarFactura();
                            break;
                        }
                        else if(opciones == 4){
                            printf("\n\n\n\t\t\t\tHas elegido salir...\t\t\t\t");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        else{
                            printf("\n\t\t\t ***** La opcion no existe ****");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        break;
                    }
                    case 4:{
                        int sal;
                        char en[10];
                        system("cls");
                        printf("\n\t\t***** ENTRADAS Y SALIDAS DE PRODUCTOS *****");
                        printf("\n\t---------------------------------------------");
                        printf("\n\t1.-Ingresar cantidad");
                        printf("\n\t2.-Restar cantidad");
                        printf("\n\t---------------------------------------------");
                        do{
                            printf("\n\tSelecciones una opcion: ");
                            scanf("%s",en);
                            N=validar_numero(en);
                        }while (N==0);
                        sal=atoi(en);
                        if(sal==1){
                            entradas();
                        }
                        else if(sal==2){
                            salida();
                        }
                        else{
                            printf("\n\t\t\t ***** La opcion no existe ****");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        break;
                    }
                    case 5:{
                        int busqueda;
                        int codb=0;
                        system("cls");
                        printf("\n\t\t ***** BUSQUEDA DE PRODUCTOS *****");
                        printf("\n\t-----------------------------------------------------------------");
                        printf("\n\tIngrese el codigo del Producto: ");
                        scanf("%d",&busqueda);
                        for(i=1;i<j;i++){
                            if(busqueda==bodega[i].id){
                                codb=i;
                            }
                        }
                        if(codb==0){
                            printf("\n\t\t\t ¡El producto no existe!");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        else{
                            printf("\n\t-----------------------------------------------------------------");
                            printf("\n\tCOD\t\t\tPRODUCTO\t\t\tLOTE\t\tSTOCK\t\tPRECIO\t\tTOTAL");
                            printf("\n\t%d\t\t%s\t\t\t%s\t\t%d\t\t%.2f$\t\t%.2f$",bodega[codb].id,bodega[codb].nomPro,bodega[codb].lote,bodega[codb].cantidad,bodega[codb].precio,bodega[codb].total);
                            printf("\n\t-----------------------------------------------------------------");
                            printf("\n\t\tPara regresar al menu anterior presione 1 ");
                            printf("\n\t1.-SI: ");
                            int y;
                            scanf("%d",&y);
                            if(y==1){
                                break;
                            }
                            else{
                                break;
                            }
                        }
                    }
                    case 6:{
                      system("cls");
                        informacion[codU].id;
                        eliminar();
                        break;
                    }
                    case 7:{
                        system("cls");
                            informacion[codU].id;
                            printf("\n\t\t\t***** Usuarios del Sistema *****");
                            printf("\n\t------------------------------------------------");
                            printf("\n\tNOMBRE\t\t\t\tCEDULA\t\t\tTELEFONO");
                            printf("\n\t------------------------------------------------");
                            for(i=1;i<l;i++){
                                printf("\n\t%s %s\t\t\t%d\t\t%d",informacion[i].nombre,informacion[i].apellido,informacion[i].cedula,informacion[i].telf);
                            }
                            printf("\n\t------------------------------------------------");
                            printf("\n\t\tPara regresar al menu anterior presione 1 ");
                            printf("\n\t1.-SI: ");
                            int y;
                            scanf("%d",&y);
                            if(y==1){
                                break;
                            }
                            else{
                                break;
                            }
                    }
                    case 8:{
                        system("cls");
                        printf("\n\t\t\t*** Sistema de cambio de clave ***\n");
                        Cambiocontra();
                        break;
                    }
                    case 9:{
                        system("cls");
                        printf("\n\t\t\t*** Sistema de cambio de usuario ***\n");
                        Cambiousu();
                        break;
                    }
                    case 10: {
                        system("cls");
                        clientesag();
                        break;
                    }
                    case 11: {
                        system("cls");
                        printf("\n\t\t\t***  Clientes ***\n");
                        clientesmos();
                        break;
                    }
                    case 12: {
                        system("cls");
                        printf("\n\t\t\t*** Sistema de eliminacion de clientes ***\n");
                        clientesDELETE();
                        break;
                    }
                    case 13:{
                        system("cls");
                        printf("\n\t\t\t***** HASTA PRONTO *****");
                        exit(0);
                        break;
                    }
                    default:printf("\n\t\t ***** La opcion no existe *****");
                    Sleep(2000);
                    system("cls");
                }   
                intento=4;
            }
            while(ac!=7); 
        }
        else{
            system("cls");
            printf("\n\t\t\t\tUsuario o clave incorreto");
            intento++;
            if (intento>3){
                printf("\n\t\t-----Has superado el numero de intentos-----");
                exit(0);
            }
        }
    }
    while(intento<=3);
}

crearUsuario crear(int IdU)
{
    crearUsuario informacion;
    FILE * datosusuario;
    usuarios = fopen("Datos/nuevoUsu.txt", "a");
    datosusuario = fopen("Datos/datosus.txt", "a");
    informacion.id = IdU;
    printf("\n\t\tIngrese la siguiente informacion");
    do {
        printf("\n\tIngrese su cedula: ");
        scanf("%s", & cedula);
        N = validar_numero(cedula);
    } while (N == 0);
    informacion.cedula = atoi(cedula);
    do {
        printf("\n\tIngrese solo Letras");
        printf("\n\tIngrese su Nombre: ");
        scanf("%s", informacion.nombre);
        M = validar_letras(informacion.nombre);
    } while (M == 0);
    do {
        printf("\n\tIngrese solo letras");
        printf("\n\tIngrese su Apellido: ");
        scanf("%s", informacion.apellido);
        M = validar_letras(informacion.apellido);
    } while (M == 0);
    do {
        printf("\n\tIngrese su Telefono:");
        scanf("%s", telefono);
        N = validar_numero(telefono);
    } while (N == 0);
    informacion.telf = atoi(telefono);
    fprintf(datosusuario, "\n%d %d %s %s %d", informacion.id, informacion.cedula, informacion.nombre, informacion.apellido, informacion.telf);
    fclose(datosusuario);
    fprintf(usuarios, "%d\n", IdU);
    printf("\n\tIngrese un nombre de Usuario: ");
    scanf("%s", usu);
    fprintf(usuarios, "%s\n", usu);
    printf("\n\tIngrese una contrase%ca unica: ",164);
    scanf("%s", clave);
    fprintf(usuarios, "%s\n", clave);
    fclose(usuarios);
    return (informacion);
}

productoEstructura ingresoPro(int idp)
{
    productoEstructura bodega;
    char ca[10];
    FILE *Inventario;
    FILE *InventarioFinal;
    InventarioFinal=fopen("Datos/InventarioFinal.txt","ab");
    Inventario=fopen("Datos/inventario.txt","ab");
    bodega.id=idp;
    printf("\n\t\tIngrese los siguientes datos del producto");
    printf("\n\t\tPRODUCTO:");
    while(getchar()!='\n');
    fgets(bodega.nomPro,100,stdin);
    strcpy(bodega.nomPro,strtok(bodega.nomPro,"\n"));
    printf("\n\t\tLOTE: ");
    scanf("%s",bodega.lote);
    do{
        printf("\n\t\tSTOCK: "),
        scanf("%s",ca);
        N=validar_numero(ca);
    }while(N==0);
    bodega.cantidad=atoi(ca);
    printf("\n\t\tPRECIO DE COMPRA: ");
    scanf("%f",&bodega.precio);
    bodega.total=bodega.cantidad*bodega.precio;
    fprintf(Inventario,"\n%d %s\n%d %f %f %s",bodega.id,bodega.nomPro,bodega.cantidad,bodega.precio,bodega.total,bodega.lote);
    fprintf(InventarioFinal,"\n%d %s %s %d %f %f",bodega.id,bodega.nomPro,bodega.lote,bodega.cantidad,bodega.precio,bodega.total);
    fclose(InventarioFinal);
    fclose(Inventario);
    return bodega;
}

void cargar()
{
    FILE *abrir;
    abrir=fopen("Datos/inventario.txt","r");
    if (abrir!=NULL){
        while(feof(abrir)==0){
            fscanf(abrir,"%d",&bodega[j].id);
            fgets(bodega[j].nomPro,100,abrir);
            strcpy(bodega[j].nomPro,strtok(bodega[j].nomPro,"\n"));
            fscanf(abrir,"%d",&bodega[j].cantidad);
            fscanf(abrir,"%f",&bodega[j].precio);
            fscanf(abrir,"%f",&bodega[j].total);
            fscanf(abrir,"%s",bodega[j].lote);
            j++;
        }
        fclose(abrir);
    }
}

void cargar1()
{
    FILE *cargarU;
    cargarU=fopen("Datos/datosus.txt","r");
    if(cargarU!=NULL){
        while(feof(cargarU)==0){
            fscanf(cargarU,"%d",&informacion[l].id);
            fscanf(cargarU,"%d",&informacion[l].cedula);
            fscanf(cargarU,"%s",informacion[l].nombre);
            fscanf(cargarU,"%s",informacion[l].apellido);
            fscanf(cargarU,"%d",&informacion[l].telf);
            l++;
        }
        fclose(cargarU);
    }
}

void entradas()
{
    int c;
    char nu[10];
    FILE *entrada;
    system("cls");
    printf("\n\t\t\t***** PRODUCTOS EXISTENTES EN BODEGA *****");
    printf("\n\t-----------------------------------------------------------------");
    printf("\n\tCOD\t\t\tPRODUCTO\t\t\tLOTE\t\tSTOCK\t\tPRECIO\t\tTOTAL");
    for(i=1;i<j;i++){
        printf("\n\t%d\t\t%s\t\t\t%s\t\t%d\t\t%.2f$\t\t%.2f$",bodega[i].id,bodega[i].nomPro,bodega[i].lote,bodega[i].cantidad,bodega[i].precio,bodega[i].total);
    }
    printf("\n\t-----------------------------------------------------------------");

    printf("\n\t\tIngrese el codigo del Producto a agregar stock: ");
    scanf("%d",&c);
    printf("\n\t\tProducto seleccionado: %s",bodega[c].nomPro);
    do{
        printf("\n\t\tIngrese la cantidad a agregar: ");
        scanf("%s",nu);
        N=validar_numero(nu);
    }while(N==0);
    bodega[c].cantidad=bodega[c].cantidad+atoi(nu);
    bodega[c].total=bodega[c].cantidad*bodega[c].precio;
    actualizar();
}

void salida()
{
    int c;
    char nu[10];
    FILE *salidas;
    system("cls");
    printf("\n\t\t*****PRODUCTOS EXISTENTES EN BODEGA*****");
    printf("\n\t-----------------------------------------------------------------");
    printf("\n\tCOD\t\t\tPRODUCTO\t\t\tLOTE\t\tSTOCK\t\tPRECIO\t\tTOTAL");
    for(i=1;i<j;i++){
        printf("\n\t%d\t\t%s\t\t\t%s\t\t%d\t\t%.2f$\t\t%.2f$",bodega[i].id,bodega[i].nomPro,bodega[i].lote,bodega[i].cantidad,bodega[i].precio,bodega[i].total);
    }
    printf("\n\t-----------------------------------------------------------------");

    printf("\n\t\tIngrese el codigo del Producto a restar stock: ");
    scanf("%d",&c);
    printf("\n\t\tProducto seleccionado: %s",bodega[c].nomPro);
    do{
        printf("\n\t\tIngrese la cantidad a restar: ");
        scanf("%s",nu);
        N=validar_numero(nu);
    }while(N==0);
    bodega[c].cantidad=bodega[c].cantidad-atoi(nu);
    bodega[c].total=bodega[c].cantidad*bodega[c].precio;
    actualizar();
}
int validar_numero(char numero[])
{
    int i;
    for(i=0; i<strlen(numero); i++)
    {
        if(!(isdigit(numero[i])))
        {
            printf("\n\t¡Ingresa solo Numeros!\n");

            return 0;
        }
    }
    return 1;
}
int validar_letras(char numero[])
{
    int i;
    for(i=0; i<strlen(numero); i++)
    {
        if(!(isdigit(numero[i])))
        {
            return 1;
        }
    }
    return 0;
}

void actualizar()
{
    int a;
    FILE *actual;
    FILE *actualizarInventario;
    if(remove("Datos/inventario.txt")==0)
    {
        actual=fopen("Datos/inventario.txt","ab");
        remove("Datos/InventarioFinal.txt");
        actualizarInventario=fopen("Datos/InventarioFinal.txt","ab");
        for(a=1;a<j;a++){
            fprintf(actual," %d %s\n%d %f %f %s",bodega[a].id,bodega[a].nomPro,bodega[a].cantidad,bodega[a].precio,bodega[a].total,bodega[a].lote);
            fprintf(actualizarInventario,"\n%d %s %s %d %f %f",bodega[a].id,bodega[a].nomPro,bodega[a].lote,bodega[a].cantidad,bodega[a].precio,bodega[a].total);
        }
    }
    fclose(actualizarInventario);
    fclose(actual);
}

void eliminar()
{
    int a,n,t;
    printf("\n\t\t\t***** PRODUCTOS EXISTENTES EN BODEGA *****");
    printf("\n\t-----------------------------------------------------------------");
    printf("\n\tCOD\t\t\tPRODUCTO\t\t\tLOTE\t\tSTOCK\t\tPRECIO\t\tTOTAL");
    for(i=1;i<j;i++){
        printf("\n\t%d\t\t%s\t\t\t%s\t\t%d\t\t%.2f$\t\t%.2f$",bodega[i].id,bodega[i].nomPro,bodega[i].lote,bodega[i].cantidad,bodega[i].precio,bodega[i].total);
    }
    printf("\n\t-----------------------------------------------------------------");
    printf("\n\tIngrese el codigo del producto a eliminar: ");
    scanf("%d",&a);
    printf("\n\tProducto seleccionado: %s",bodega[a].nomPro);
    printf("\n\tEsta seguro de eliminar el producto? 1.-Si 2.-No: ");
    scanf("%d",&t);
    if(t==1){
        int eliminar=bodega[a].id;
        for(i=1;i<j;i++){
            if(i==a){
                while(i<=j-1){
                    bodega[i].id=bodega[i].id;
                    strcpy(bodega[i].nomPro,bodega[i+1].nomPro);
                    bodega[i].cantidad=bodega[i+1].cantidad;
                    bodega[i].total=bodega[i+1].total;
                    strcpy(bodega[i].lote,bodega[i+1].lote);
                    bodega[i].precio=bodega[i+1].precio;
                    i++;
                }
                break;
            }
        }
        j=j-1;
        printf("\n\t\t\t***** PRODUCTOS EXISTENTES EN BODEGA *****");
        printf("\n\t-----------------------------------------------------------------");
        printf("\n\tCOD\t\t\tPRODUCTO\t\t\tLOTE\t\tSTOCK\t\tPRECIO\t\tTOTAL");
        for(i=1;i<j;i++)
        {
            printf("\n\t%d\t\t%s\t\t\t%s\t\t%d\t\t%.2f$\t\t%.2f$",bodega[i].id,bodega[i].nomPro,bodega[i].lote,bodega[i].cantidad,bodega[i].precio,bodega[i].total);
        }
        printf("\n\t-----------------------------------------------------------------");
    }
    else{
        printf("\n\t\tNo se elimino el Producto"); 
    }
    actualizar();
}

void Cambiocontra() 
{
    char password[30];
    char nueva_pass[30], texto[30];
    char lineausuario[30], lineapassword[30], codUsu[10];

    int objetivo = 0; // linea para ser eliminada
    int contador = 1;
    int editar = 1;

    FILE * copia;

    usuarios = fopen("Datos/nuevoUsu.txt", "r");
    copia = fopen("Datos/temp.txt", "w"); // craemos archivo temporal

    printf("\n\t\t\tSesion iniciada como: %s", usuario_global);
    printf("\n\n\t\tIngrese su antigua clave: ");
    scanf("%s", & password);

    // Encontrar línea de la contraseña a editar
    while (!feof(usuarios)) {
        fgets(codUsu, 10, usuarios);

        if (fgets(lineausuario, 100, usuarios) != NULL) {
            if (fgets(lineapassword, 100, usuarios) != NULL) {

                // Copiamos datos originales
                fprintf(copia, codUsu);
                fprintf(copia, lineausuario);
                fprintf(copia, lineapassword);

                // Eliminamos saltos de líneas
                strcpy(lineausuario, strtok(lineausuario, "\n"));
                strcpy(lineapassword, strtok(lineapassword, "\n"));

                // Si coinciden credenciales
                if (strcmp(usuario_global, lineausuario) == 0 && strcmp(password, lineapassword) == 0) {
                    objetivo += 3;
                    editar = 0;

                }

                if (editar != 0) {
                    objetivo += 3;
                }
            }
        }
    }

    fclose(usuarios);
    fclose(copia);

    // Se encontró credenciales, y se tiene la línea de la contraseña a editar
    if (editar == 0) {
        usuarios = fopen("Datos/nuevoUsu.txt", "w");
        copia = fopen("Datos/temp.txt", "r");

        while (fgets(texto, sizeof(texto), copia) != NULL) {

            if (contador != objetivo) { // no es la línea a cambiar, se coloca lo mismo
                fprintf(usuarios, texto);

            } else {
                fflush(stdin);
                printf("\n\t\tInsertar nueva clave: ");
                scanf("%s", & nueva_pass);
                fprintf(usuarios, "%s\n", nueva_pass);
            }

            contador++;

        }

        fclose(usuarios);
        fclose(copia);
        remove("Datos/temp.txt");

        fflush(stdin);
        printf("\n\t\tClave cambiada exisitosamente\n");
        getchar();

    } else {
        fflush(stdin);
        printf("\n\t\tCredenciales incorrectas");
        getchar();
    }

}

void Cambiousu() 
{

    char nuevo_user[30], texto[30];
    char lineausuario[30], lineapassword[30], codUsu[10];

    int objetivo = 0; // linea para ser eliminada
    int contador = 1;
    int editar = 1;

    FILE * copia;

    usuarios = fopen("Datos/nuevoUsu.txt", "r");
    copia = fopen("Datos/temp.txt", "w"); // craemos archivo temporal

    printf("\n\t\t\tSesion iniciada como: %s", usuario_global);

    // Encontrar línea de la contraseña a editar
    while (!feof(usuarios)) {
        fgets(codUsu, 10, usuarios);

        if (fgets(lineausuario, 100, usuarios) != NULL) {

            strcpy(lineausuario, strtok(lineausuario, "\n"));

            if (strcmp(usuario_global, lineausuario) == 0) {
                objetivo += 2;
                editar = 0;
            }

            if (fgets(lineapassword, 100, usuarios) != NULL) {

                // Copiamos datos originales
                fprintf(copia, codUsu);
                fprintf(copia, "%s\n", lineausuario);
                fprintf(copia, lineapassword);

                // Si coinciden credenciales
                if (editar != 0) {
                    objetivo += 3;

                }
            }
        }
    }

    fclose(usuarios);
    fclose(copia);

    if (editar == 0) {
        fflush(stdin);
        usuarios = fopen("Datos/nuevoUsu.txt", "w");
        copia = fopen("Datos/temp.txt", "r");

        while (fgets(texto, sizeof(texto), copia) != NULL) {

            if (contador != objetivo) {
                fprintf(usuarios, texto);

            } else {
                fflush(stdin);
                printf("\n\t\tInsertar nuevo usuario: ");
                scanf("%s", & nuevo_user);

                fprintf(usuarios, "%s\n", nuevo_user);
                strcpy(usuario_global, nuevo_user); // cambiamos sesión
            }

            contador++;
        }

        fclose(usuarios);
        fclose(copia);
        remove("Datos/temp.txt");

        fflush(stdin);
        printf("\n\t\tusuario cambiado exisitosamente\n");
        getchar();

    } else {
        fflush(stdin);
        printf("\n\t\t ha ocurrido un error");
        getchar();
    }

}

void clientesag() {
    clientesDat Datos;
    FILE * archivo;
    archivo = fopen("Datos/Datosclientes.txt", "ab");
    if (archivo == NULL) {
        printf("error al abrir el archivo %s", archivo);

    } else {
        printf("\n\t\t Ingrese siguientes datos");
        fflush(stdin);
        printf("\n\tingrese su nombre:");
        gets(Datos.nomb);

        printf("\n\tingrese su apellido:");
        gets(Datos.apell);

        printf("\n\tingrese su cedula:");
        gets(Datos.ced);

        printf("\n\tingrese su numero telefonico:");
        gets(Datos.phone);

        fprintf(archivo, "%s\n%s\n%s\n%s\n", Datos.nomb, Datos.apell, Datos.ced, Datos.phone);

        fclose(archivo);

    }
    fclose(archivo);
}

void clientesmos() {
    char texto[30];
    clientesDat Datos;
    FILE * archivo;
    archivo = fopen("Datos/Datosclientes.txt", "r");

    if (archivo == NULL) {
        printf("error al abrir el archivo %s", archivo);

    } else {

        printf("\n\t-------------------------------------------------------");
        printf("\n\tNOMBRE\tAPELLIDO CEDULA\tTELEFONO");
        printf("\n\t------------------------------------------------");

        while (fgets(texto, 30, archivo) != NULL) {

            if (texto[0] == '\0' || texto[0] == ' ') {
                break;
            }

            fflush(stdin);
            //nombre 
            strcpy(Datos.nomb, strtok(texto, "\n"));

            //apellido
            fgets(texto, 30, archivo);
            strcpy(Datos.apell, strtok(texto, "\n"));
            //cedula
            fgets(texto, 30, archivo);
            strcpy(Datos.ced, strtok(texto, "\n"));

            //telefono
            fgets(texto, 30, archivo);
            strcpy(Datos.phone, strtok(texto, "\n"));

            printf("\n\n");
            printf("\t%s %s  \t %s  \t  %s", Datos.nomb, Datos.apell, Datos.ced, Datos.phone);
        }

    }

	printf("\n");
    fflush(stdin);
    getchar();

}

void clientesDELETE() {
    char texto[30];
    char cedula[30];
    int editar = 1;
    int objetivo = 0;
    int contador = 1;
    clientesDat Datos;
    FILE * archivo;
    FILE * copia;
    archivo = fopen("Datos/Datosclientes.txt", "r");
    copia = fopen("Datos/temp.txt", "w");
    if (archivo == NULL) {
        printf("error al abrir el archivo %s", archivo);

    }
    clientesmos();
    fflush(stdin);
    printf("\nInsertar cedula del cliente a eliminar\n>>> ");
    gets(cedula);

    while (fgets(texto, 30, archivo) != NULL) {

        //EVITAMOS LOS ERRORES CON ESPACIOS EN BLANCO 
        if (texto[0] == '\0' || texto[0] == ' ') {
            break;
        }
    

    fprintf(copia, texto); //nombre

    fgets(texto, 30, archivo);
    fprintf(copia, texto);

    fgets(texto, 30, archivo); // cedula
    fprintf(copia, texto);
	

	strcpy(texto, strtok(texto, "\n"));
	strcpy(texto, strtok(texto, " "));

	if (strcmp(cedula, strtok(texto, "\n")) == 0) {
        editar = 0;
        objetivo += 1;

    }
    
    fgets(texto, 30, archivo);
    fprintf(copia, texto);

    if (editar != 0) {
        objetivo += 1;
    }
    
	}

    fclose(archivo);
    fclose(copia);

	fflush(stdin);
	getchar();
		
    if (editar == 0) {
        fflush(stdin);
        archivo = fopen("Datos/Datosclientes.txt", "w");
        copia = fopen("Datos/temp.txt", "r");

        while (fgets(texto, 30, copia) != NULL && texto[0] != '\0' && texto[0] != ' ') {
			printf("Nombre: %s", texto);
            //EVITAMOS LOS ERRORES CON ESPACIOS EN BLANCO 
            if (texto[0] == '\0' || texto[0] == ' ') {
                break;
            }
			printf("contador:%d\nobjetivo:%d\n", contador, objetivo);
			
            if (contador != objetivo) {
                fprintf(archivo, texto); //nombre

                fgets(texto, 30, copia);
                fprintf(archivo, texto);

                fgets(texto, 30, copia);
                fprintf(archivo, texto);

                fgets(texto, 30, copia);
                fprintf(archivo, texto);

            } else {
            	// Leemos el resto y nos lo saltamos
            	fgets(texto, 30, copia);
            	fgets(texto, 30, copia);
            	fgets(texto, 30, copia);

			}

            contador++;
        }

        fclose(archivo);
        fclose(copia);
        remove("Datos/temp.txt");

        fflush(stdin);
        printf("\n\t\t Cliete borrado exitosamente\n");
        getchar();

    } else {
        fflush(stdin);
        printf("\n\t\t Cliete no encontrado\n");
        getchar();
    }
}

void tienpo()
{
    FILE    *file; 
    time_t  tiempo;
    struct  tm  *timelocal;
    char out_time[128],  t[25];

    tiempo = time(0);
    timelocal = localtime(&tiempo);
    strftime(out_time, sizeof(out_time), "%d/%m/%y  %H:%M:%S", timelocal);
    if ( ((file = fopen(NOM_FILE, "a")) == NULL) || ((file = fopen(NOM_FILE, "r")) == NULL))
        file = fopen(NOM_FILE, "w");
    if ( (file = fopen(NOM_FILE, "a")) == NULL)
    {
        perror(NOM_FILE);
        return EXIT_FAILURE;
    }

    fprintf(file, "%s\n", out_time);
    fclose(file);

    if ( (file = fopen(NOM_FILE, "r")) == NULL)
    {
        perror(NOM_FILE);
        return EXIT_FAILURE;
    }
    printf("fecha de creacion de las facturas:\n");
    while (fgets(t, (int) sizeof t, file) != NULL)
    printf("%s",t);
    Sleep(4000);
    system("cls");

    fclose(file);   
    return(0);
}

void guardarfactura()
{
    ptr=fopen(clientefactura, "a+");
    if(ptr==NULL){
        system("cls");
        printf("Error en el achivo");
        return;
    }
    else{
        for (f=0; f<cantcompra;f++)
        {
            fwrite(&factura[f],sizeof(factura[f]),1,ptr);
        }
        
        fclose(ptr);
        system("cls");
        gotoxy(25,3);
        printf("Factura guardada...");
        gotoxy(28,8);
        printf("Gracias por su compra!..");

        Sleep(2000);
        system("cls");
        

    }
}

//Esta funcion me realiza el trabajo de factura todo, y tambien de clacular el total
void facturar()
{
    FILE    *file;
    time_t  tiempo;
    struct  tm  *timelocal;
    char    out_time[128],  t[25];
    short cont=1, grfactura, opcfactura, cantnom;
    float acumulador=0;
    
    char cant[10];
    FILE *salidas;
    system("cls");
    printf("\n\t\t*****PRODUCTOS EXISTENTES EN BODEGA*****");
    printf("\n\t-----------------------------------------------------------------");
    printf("\n\tCOD\t\t\tPRODUCTO\t\t\tLOTE\t\tSTOCK\t\tPRECIO\t\tTOTAL");
    for(i=1;i<j;i++){
        printf("\n\t%d\t\t%s\t\t\t%s\t\t%d\t\t%.2f$\t\t%.2f$",bodega[i].id,bodega[i].nomPro,bodega[i].lote,bodega[i].cantidad,bodega[i].precio,bodega[i].total);
    }
    printf("\n\t-----------------------------------------------------------------");
    
    gotoxy(34,3);
    gotoxy(17,20);
    fflush(stdin);
    printf("Nombre del cliente: ");
    scanf("%[^\n]s", &factura[0].nombreCliente);
    gotoxy(12,23);
    printf("Cantidad ");
    gotoxy(27,23);
    printf("codigo del Producto ");
    gotoxy(55,23);
    printf("Producto ");
    gotoxy(80,23);
    printf("Precio ");
    gotoxy(95,23);
    printf("Total ");

    cantnom=strlen(factura[0].nombreCliente);

    for(z=0;z<=cantnom;z++){
        clientefactura[z]=factura[0].nombreCliente[z];
    }
    strcat(clientefactura, "Factura.txt");
        f=0;
        cantcompra=0;
        x=14;
        y=24;
        
    
    while(cont>=1)
    {
        printf("\n");
        printf("            ");
        fflush(stdin);
        gotoxy(x,y);
        scanf("%f", &factura[f].cantidad);
        fflush(stdin);
        gotoxy(x+20,y);
        scanf("%d",&d);
        fflush(stdin);
        gotoxy(x+35,y);
        scanf("%[^\n]s", &factura[f].nomPro);
        fflush(stdin);
        gotoxy(x+65,y);
        scanf("%f",&factura[f].precio);
        fflush(stdin);
        gotoxy(x+75,y);
        factura[f].total=factura[f].cantidad*factura[f].precio;
        printf("%.2f$", factura[f].total);
        acumulador+=factura[f].total;
        gotoxy(75,26);
        fflush(stdin);

        factura[f].totalaPagar=acumulador;
        bodega[d].cantidad=bodega[d].cantidad-factura[f].cantidad;
        bodega[d].total=bodega[d].cantidad*bodega[d].precio;
        actualizar();

        gotoxy(95,20);
        printf("Agregar mas?(1/0): ");
        scanf("%d", &cont);
        f++;
        cantcompra++;
        y+=1;
        
    }

    gotoxy(45,y+4);
    gotoxy(115,30);
    printf("Total a pagar: %.2f$", acumulador);
    gotoxy(35,y+7);
    gotoxy(110,32);
    printf("Quieres guardar esta factura? (1/0): ");
    scanf("%d", &grfactura);

    y=24;

    if(grfactura>=1){
        tienpo();
        guardarfactura();
    }
    else{
        system("cls");
        gotoxy(5,3);
        printf("Desea volver a hacer otra factura?(1/0): ");
        scanf("%d", &opcfactura);
        if(opcfactura>=1){
            system("cls");
            facturar();
        }
        else{
            system("cls");
        }
    }
}

//Esta funcion me permite el historial de compras de un cliente
void VerFactura()
{
    short cantn, cont=0, otrocliente;
    char nom[20], nomcliente[50];
    
    
    system("cls");
    gotoxy(20,3);
    printf("Ha elegido la opcion de Ver facturas");
    gotoxy(25,7);
    printf("Digite el nombre del cliente: ");
    fflush(stdin);
    scanf("%[^\n]s", nom);
    cantn=strlen(nom);
    for(z=0;z<=cantn;z++){
        nomcliente[z]=nom[z];
    }
    strcat(nomcliente, "Factura.txt");

    ptr=fopen(nomcliente,"r");
    if(ptr==NULL){
            system("cls");
            gotoxy(15,4);
        printf("Error al leer, la factura de ese cliente no existe");
        Sleep(2000);
        system("cls");
        

    }
    else{
        system("cls");
        f=0;
        x=14;
        y=12;
        while (!feof(ptr))
        {
            cont=fread(&factura[f], sizeof(factura[f]),1,ptr);
            if(cont==1){
                gotoxy(20,3);
                printf("Factura del cliente: %s",nom);
                gotoxy(12,10);
                printf("Cantidad ");
                gotoxy(x,y);
                printf("%.f", factura[f].cantidad);
                 gotoxy(35,10);
                printf("producto ");
                gotoxy(x+12,y);
                printf("%s",factura[f].nomPro);
                gotoxy(58,10);
                printf("Precio ");
                gotoxy(x+44,y);
                printf("%.2f$",factura[f].precio);
                gotoxy(70,10);
                printf("Total ");
                gotoxy(x+56,y);
                printf("%.2f$", factura[f].total);
                gotoxy(100,10);
                printf("Total de la compra");
                printf("\n\t\t\t\t\t\t\t\t\t\t\t\t--------------");
                gotoxy(102,12);
                printf("%.2f$", factura[f].totalaPagar);

                f++;
                y+=1;
            }
        }
        fclose(ptr);
        gotoxy(45,7);
        fflush(stdin);
        printf("Ver otro cliente?(1/0): ");
        scanf("%d", &otrocliente);
        if(otrocliente>=1){
            system("cls");
            VerFactura();
        }
        else{
            system("cls");
        }  
    }

}

//Esta funcion me elimina el archivo de un cliente con solo digitar su nombre 
void BorrarFactura()
{
    char borrarfac[20], borrardir[10]="erase \\ ";

    system("cls");

    gotoxy(2,7);
    printf("Digite el cliente que desea eliminar: ");
    fflush(stdin);
    scanf("%[^\n]s", &borrarfac);

    strcat(borrardir, borrarfac);
    strcat(borrardir, "Factura.txt");

        gotoxy(14,10);
    if(system(borrardir)==NULL){
        system("cls");
        gotoxy(15,10);
        printf("Se ha eliminado la factura o ya no existia...");
        Sleep(2000);
        system("cls");
        
    }
    else{
        system("cls");
        gotoxy(15,10);
        printf("No se ha eliminado la factura o no exixtia...");
        Sleep(2000);
        system("cls");

    } 
}

void ayuda() {
	printf("\n--------------------------------------------------------------\n\n");
	printf("\nNombre del sistema: Compras PatriElectronics\n");
	printf("\nCreadores del Programa:\nEdylis Bellorin C.I:27878223  \nCarlos Moya C.I:31317884  \nGobert Pinnago C.I:30656753  \nAngel Rodriguez C.I:30437205  \nManuel Rodriguez C.I:30292820\n");
	printf("\nCarrera: Ingenieria Informatica Seccion 2\n");
	printf("\n2do Semestre\n");
	printf("\nCreado en el a%co: 2022\n\n",164);
	printf("\n--------------------------------------------------------------\n");
	printf("\n\t\t***** GRACIAS POR USAR PATRIELECTRONICS *****\n\n ");
	
	}