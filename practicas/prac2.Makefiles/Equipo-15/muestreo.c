#include<stdio.h>
#include<math.h>
#include"defs.h"
#include"procesamiento.h"
#include"archivos.h"

int main(){
	float seno[MUESTRAS];

	genera_seno( seno );
	guarda_datos( seno );

	return 0;
}
