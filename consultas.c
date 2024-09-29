//programa en C para consultar los datos de la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	//Creamos una conexion al servidor MYSQL
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexi\u1162\u1108n: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializamos la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "juego",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexi\u1162\u1108n: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	// Preguntamos por el nombre del jugador X del cual queremos saber el numero de partidas jugadas
	char username[60];
	printf("Introduce el nombre del jugador que deseas buscar: ");
	scanf("%s", username);
	
	// Hacemos una consulta para obtener el numero de partidas en las que esta jugando X jugador	
	char consulta[256];
	snprintf(consulta, sizeof(consulta),
			 "SELECT COUNT(DISTINCT PUENTE.ID_MATCH) AS NUMERO_DE_PARTIDAS "
			 "FROM PLAYERS, PUENTE, MATCHES "
			 "WHERE PLAYERS.USERNAME = '%s' " // Usamos el nombre del jugador que se ha introducido por el terminal
			 "AND PLAYERS.ID = PUENTE.ID_PLAYER", username);
	
	err=mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//Recogemos el resultado de la consulta. 
	resultado = mysql_store_result (conn);
	if (resultado == NULL) {
		printf("Error al almacenar el resultado de la consulta: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	row = mysql_fetch_row (resultado);
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else{
		// Mostramos el numero de partidas en las que esta jugando X
			printf("El jugador %s esta jugando en %s partidas\n", username, row[0]);
	}
		
		mysql_close (conn);
		exit(0);
}
