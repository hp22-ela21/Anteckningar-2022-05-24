/**********************************************************************************
* I C finns ett fåtal standarddataströmmar som alla utgör olika typer av filpekare 
* (FILE* från biblioteket stdio.h):
* 
* Standardenheten stdout används för utskrift till konsolen.
* Standardinenheten stdin används för inmatning från konsolen.
* Standardfelenheten stderr används för felutskrift, vanligtvis via konsolen.
* 
* Förutom ovanstående standardströmmar kan användaren skriva till eller läsa 
* från en specifik filsökväg genom att deklarera en egen filström via en 
* filpekare, där ett flertal modes kan välja, exempelvis w (write) för att
* skriva till en fil, där befintligt innehåll skrivs över, r (read) för att
* läsa innehåll från en fil samt a (append) för att lägga till innehåll i en
* fil utan att radera befintligt innehåll.
* 
* För att öppna en fil för skrivning kan följande instruktion användas:
* FILE* file = fopen("filepath.txt", "w);
* 
* För att öppna en fil för att bifoga innehåll kan följande instruktion användas:
* FILE* file = fopen("filepath.txt", "a");
* 
* För att öppna en fil för läsning kan följande instruktion användas:
* FILE* file = fopen("filepath.txt", "r");
* 
* Om filen inte gick att öppna returneras en nullpekare. Kontroll av 
* returvärdet efter anrop av funktionen fopen bör därmed kontrolleras.
* Om filen inte gick att öppna bör funktionen avslutas, alternativt med
* ett felmeddelande:
* 
* if (!fstream)
* {
*    fprintf(stderr, "Could not open file at path %s!\n\n", filepath);
*    return;
* }
* 
* Filskrivning kan sedan ske via anrop av funktionen fprintf:
* fprintf(fstream, "This data is written to the file!\n");
* 
* Precis som funktionen printf kan innehåll från variabler och konstanter
* skrivas via användning av motsvarande formatspecificerare, exempelvis
* fprintf(fstream, "Writing integer %d\n" 5);
* fprintf(fstream, "My name is %s\n", name);
* 
* För att läsa en rad från en fil och spara i en sträng döpt s kan anrop av
* funktionen fgets användas, vilket också gäller för inläsning från konsolen:
* fgets(s, sizeof(s), fstream);
* 
* Efter skrivning eller läsning är färdig bör filen stängas, vilket åstadkommes
* via anrop av funktionen fclose, där aktuell filpekare passeras som argument:
* fclose(fstream);
**********************************************************************************/

/* Inkluderingsdirektiv: */
#include <stdio.h>

/**********************************************************************************
* Skriver en rad med text till en fil. Eventuellt föregående innehåll raderas. 
* Ingående argument filepath utgör filsökvägen, medan s utgör textraden som skall 
* skrivas till filen.
**********************************************************************************/
static void file_write(const char* filepath, const char* s)
{
   FILE* fstream = fopen(filepath, "w");

   if (!fstream)
   {
      fprintf(stderr, "Could not open file at path %s!\n\n", filepath);
      return;
   }

   fprintf(fstream, "%s\n", s);
   fclose(fstream);
   return;
}

/**********************************************************************************
* Bifogar en rad med text till en fil. Eventuellt föregående innehåll bibehålls
* och det nya innehållet bifogas längst ned i filen. Ingående argument filepath 
* utgör filsökvägen, medan s utgör textraden som skall bifogas.
**********************************************************************************/
static void file_append(const char* filepath, const char* s)
{
   FILE* fstream = fopen(filepath, "a");

   if (!fstream)
   {
      fprintf(stderr, "Could not open file at path %s!\n\n", filepath);
      return;
   }

   fprintf(fstream, "%s\n", s);
   fclose(fstream);
   return;
}

/**********************************************************************************
* Läser varje rad från en fil en efter en och skriver ut i konsolen. Ingående
* argument filepath utgör filsökvägen som läsning skall ske från.
**********************************************************************************/
static void file_read(const char* filepath)
{
   FILE* fstream = fopen(filepath, "r"); 
   
   if (!fstream)
   {
      fprintf(stderr, "Could not open file at path %s!\n\n", filepath);
      return;
   }

   char s[100];
   s[0] = '\0';
   while (fgets(s, sizeof(s), fstream))
      fprintf(stdout, "%s", s);
   fclose(fstream);
   return;
}

/**********************************************************************************
* Skriver en rad till filen data.txt. Bifogar sedan ytterligare en rad till 
* samma fil. Läser sedan in innehållet och skriver ut i konsolen.
**********************************************************************************/
int main(void)
{
   file_write("data.txt", "C programming is fun!");
   file_append("data.txt", "Especially pointer aritmetic!");
   file_read("data.txt");
   return 0;
}