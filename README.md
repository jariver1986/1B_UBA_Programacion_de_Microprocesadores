
![image](https://github.com/user-attachments/assets/aaa8f7a4-f70d-4241-b5a5-7cdb6aaa8a97)

**Blibliografia y recursos**

“The C Programming Language”, 2nd Ed. Kernighan & Ritchie.

“Embedded C”. Michael J. Pont.  Pearson Education Ltd 2007.

Noviello, C. (2017). Mastering STM32: A step-by-step guide to the most complete ARM Cortex-M platform, using a free and powerful development environment based on Eclipse and GCC. Leanpub. Disponible en http://leanpub.com/mastering-stm32

“A Beginner's Guide to Designing Embedded System Applications on Arm Cortex-M Microcontrollers”. Lutenberg, Gomez, Pernia. Arm Education Media, 2022.

Embedded Gurus (link).

Lista embebidos32@googlegroups.com
Compilador online: https://www.onlinegdb.com/online_c_compiler

![image](https://github.com/user-attachments/assets/90e59a51-abbf-4592-a131-b98e7bb7b8f3)


Descarga Doxygen desde: https://www.doxygen.nl/download.html



En bash genera un doxifile
doxygen -g Doxyfile

Abrelo y editalo
PROJECT_NAME           = "Documentación STM32"
OUTPUT_DIRECTORY       = "docs"         # Carpeta donde se guardará la documentación
INPUT                 = "src/ led/"     # Directorios con los archivos a documentar
FILE_PATTERNS         = *.c *.h         # Extensiones de archivos a incluir
RECURSIVE             = YES             # Incluir archivos dentro de subcarpetas
GENERATE_HTML         = YES             # Generar documentación en HTML
GENERATE_LATEX        = NO              # No generar PDF (opcional)
HAVE_DOT              = YES             # Habilitar gráficos de dependencias
DOT_PATH              = /usr/bin/dot    # Ubicación de Graphviz (para gráficos)

Guarda y cierra
Ahora genera el documento
doxygen Doxyfile
Esto creará la documentación dentro de la carpeta docs/html/.
Para visualizarla, abre el archivo:
docs/html/index.html

Subir a Github
git checkout --orphan gh-pages
git rm -rf .

mv docs/html/* .

git add .
git commit -m "Publicación de documentación con Doxygen"
git push origin gh-pages


para ver con el visualizador de Gothub Pages se hace lo siguiente:
Ve a GitHub > Settings > Pages.
En Source, selecciona la rama gh-pages y guarda.
hace click en el link que te aparece y podras ver la documentacion.


![image](https://github.com/user-attachments/assets/c268f5ba-de04-4ef2-b6b6-48d8d4108e56)

![image](https://github.com/user-attachments/assets/850e8e74-be7e-47b0-9f2e-78e10dfc3673)

Practica con SD

https://github.com/eziya/STM32_SPI_SDCARD/tree/master

https://www.youtube.com/watch?v=aqSNz26Cuio&t=221s

https://www.youtube.com/watch?v=PBIm8BCnbyQ

https://www.micropeta.com/video29

## SPI2 pero tiene nombre SPI1 - Para practica con Micro SD Adapter

![image](https://github.com/user-attachments/assets/6fd3944e-6918-4266-b9e3-c79d5b1882fe)

![image](https://github.com/user-attachments/assets/155110f3-8792-4f95-8577-567e9e0a2d4b)

![image](https://github.com/user-attachments/assets/d281e0c0-dd5d-4a2e-8e6c-34ec6802ec51)

![image](https://github.com/user-attachments/assets/a6618323-59cd-4aa0-9c01-dccc437f0b99)

![image](https://github.com/user-attachments/assets/efe60ee1-9fb2-4732-964b-657edfe9c824)

```c
/* USER CODE BEGIN Header */
/**
 ******************************************************************************
  * @file    user_diskio.c
  * @brief   This file includes a diskio driver skeleton to be completed by the user.
 ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#ifdef USE_OBSOLETE_USER_CODE_SECTION_0
/*
 * Warning: the user section 0 is no more in use (starting from CubeMx version 4.16.0)
 * To be suppressed in the future.
 * Kept to ensure backward compatibility with previous CubeMx versions when
 * migrating projects.
 * User code previously added there should be copied in the new user sections before
 * the section contents can be deleted.
 */
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */
#endif

/* USER CODE BEGIN DECL */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "ff_gen_drv.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Disk status */
static volatile DSTATUS Stat = STA_NOINIT;

/* USER CODE END DECL */

/* Private function prototypes -----------------------------------------------*/
DSTATUS USER_initialize (BYTE pdrv);
DSTATUS USER_status (BYTE pdrv);
DRESULT USER_read (BYTE pdrv, BYTE *buff, DWORD sector, UINT count);
#if _USE_WRITE == 1
  DRESULT USER_write (BYTE pdrv, const BYTE *buff, DWORD sector, UINT count);
#endif /* _USE_WRITE == 1 */
#if _USE_IOCTL == 1
  DRESULT USER_ioctl (BYTE pdrv, BYTE cmd, void *buff);
#endif /* _USE_IOCTL == 1 */

Diskio_drvTypeDef  USER_Driver =
{
  USER_initialize,
  USER_status,
  USER_read,
#if  _USE_WRITE
  USER_write,
#endif  /* _USE_WRITE == 1 */
#if  _USE_IOCTL == 1
  USER_ioctl,
#endif /* _USE_IOCTL == 1 */
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes a Drive
  * @param  pdrv: Physical drive number (0..)
  * @retval DSTATUS: Operation status
  */
DSTATUS USER_initialize (
	BYTE pdrv           /* Physical drive nmuber to identify the drive */
)
{
  /* USER CODE BEGIN INIT */
	return SD_disk_initialize(pdrv);
  /* USER CODE END INIT */
}

/**
  * @brief  Gets Disk Status
  * @param  pdrv: Physical drive number (0..)
  * @retval DSTATUS: Operation status
  */
DSTATUS USER_status (
	BYTE pdrv       /* Physical drive number to identify the drive */
)
{
  /* USER CODE BEGIN STATUS */
	return SD_disk_status(pdrv);
  /* USER CODE END STATUS */
}

/**
  * @brief  Reads Sector(s)
  * @param  pdrv: Physical drive number (0..)
  * @param  *buff: Data buffer to store read data
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to read (1..128)
  * @retval DRESULT: Operation result
  */
DRESULT USER_read (
	BYTE pdrv,      /* Physical drive nmuber to identify the drive */
	BYTE *buff,     /* Data buffer to store read data */
	DWORD sector,   /* Sector address in LBA */
	UINT count      /* Number of sectors to read */
)
{
  /* USER CODE BEGIN READ */
	return SD_disk_read(pdrv, buff, sector, count);
  /* USER CODE END READ */
}

/**
  * @brief  Writes Sector(s)
  * @param  pdrv: Physical drive number (0..)
  * @param  *buff: Data to be written
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to write (1..128)
  * @retval DRESULT: Operation result
  */
#if _USE_WRITE == 1
DRESULT USER_write (
	BYTE pdrv,          /* Physical drive nmuber to identify the drive */
	const BYTE *buff,   /* Data to be written */
	DWORD sector,       /* Sector address in LBA */
	UINT count          /* Number of sectors to write */
)
{
  /* USER CODE BEGIN WRITE */
  /* USER CODE HERE */
	return SD_disk_write(pdrv, buff, sector, count);
  /* USER CODE END WRITE */
}
#endif /* _USE_WRITE == 1 */

/**
  * @brief  I/O control operation
  * @param  pdrv: Physical drive number (0..)
  * @param  cmd: Control code
  * @param  *buff: Buffer to send/receive control data
  * @retval DRESULT: Operation result
  */
#if _USE_IOCTL == 1
DRESULT USER_ioctl (
	BYTE pdrv,      /* Physical drive nmuber (0..) */
	BYTE cmd,       /* Control code */
	void *buff      /* Buffer to send/receive control data */
)
{
  /* USER CODE BEGIN IOCTL */
	return SD_disk_ioctl(pdrv, cmd, buff);
  /* USER CODE END IOCTL */
}
#endif /* _USE_IOCTL == 1 */
```

![image](https://github.com/user-attachments/assets/3f246b1d-4be3-44a3-9f1a-a09ff981019b)

![image](https://github.com/user-attachments/assets/51011b88-8037-4c93-9301-cec1dbae79ac)

## I2C settings Non - DMA to MPU6050 sensor

![image](https://github.com/user-attachments/assets/6e2e907c-9721-4786-9f08-b8cac91205d1)

![image](https://github.com/user-attachments/assets/3c5a945d-5240-46f3-8c3f-e3b3e1ea99c7)

![image](https://github.com/user-attachments/assets/04a6028f-333e-46f2-9760-29f4f221cc5a)

![image](https://github.com/user-attachments/assets/aad67831-ac9f-40bc-93e3-6e74d849f376)

![image](https://github.com/user-attachments/assets/c9abcc5a-7dd8-424f-8822-212532fb66ff)

![image](https://github.com/user-attachments/assets/cfa55beb-13e4-4174-8aa4-c63609398c35)

## SPI1 settings using ADXL345 Non HAL

![image](https://github.com/user-attachments/assets/9395e6eb-231c-4aea-847b-c8122b5f54d2)

![image](https://github.com/user-attachments/assets/d5191247-661b-4686-9e02-4e86341a467a)

![image](https://github.com/user-attachments/assets/fb27ca40-c2e4-4d87-a4f3-d01475fefe0b)














