import time
import sys

# colores para que se vea lindo
VERDE = '\033[92m'
RESET = '\033[0m'

def boot_os():

    # nvolvemos el logo con el color verde y al final lo reseteamos
    logo = f"""{VERDE}
     _   _ _   _    _    __  __        ____   ___  
    | | | | \ | |  / \  |  \/  |      / ___| / _ \ 
    | | | |  \| | / _ \ | |\/| | ____ \___ \| | | |
    | |_| | |\  |/ ___ \| |  | |      |___) | |_| |
     \___/|_| \_/_/   \_\_|  |_|      |____/ \___/ 
                                                   
    =================================================
           Simulador de Sistema Operativo v1.0
         Universidad Nacional Autonoma de Mexico

        Luisa Cristina Carranza Mendez

        
    ================================================={RESET}
    """
    
    print(logo)
    
    boot_messages = [
        f"{VERDE}Iniciando gestor de arranque...{RESET}",
        f"{VERDE}Cargando kernel del simulador... [ OK ]{RESET}",
        f"{VERDE}Montando administrador de memoria principal... [ OK ]{RESET}",
        f"{VERDE}Inicializando modulos de planificacion (Schedulers)... [ OK ]{RESET}",
        f"{VERDE}Estableciendo puente de conexion C/Python... [ OK ]{RESET}",
        f"{VERDE}Sistema montado con exito. Listo para recibir procesos.\n{RESET}"
    ]
    
    for msg in boot_messages:
        sys.stdout.write(msg + "\n")
        sys.stdout.flush()
        time.sleep(0.3)
