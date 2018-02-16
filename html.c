#include <stdio.h>

#include "html.h"

#define     HTML_OUT_FILE   "html/patients.html"

int html_create(person_t * list, unsigned nr_persons)
{
    if (nr_persons == 0) return -1;

    FILE * fp = fopen(HTML_OUT_FILE, "w");

    if (!fp) return -1;

    html_fill_header(fp);

    // Enter a new entry with the information in the list
    fprintf(fp, "<table>\n<tr>\n");
    fprintf(fp, "\t<th>Patient</th>\n");
    fprintf(fp, "\t<th>Age</th>\n");
    fprintf(fp, "\t<th>Sex</th>\n");
    fprintf(fp, "\t<th>HTA</th>\n");
    fprintf(fp, "\t<th>HSA</th>\n");
    fprintf(fp, "\t<th>Incident</th>\n");
    fprintf(fp, "\t<th>Fisher</th>\n");
    fprintf(fp, "\t<th>Glasgow</th>\n");
    fprintf(fp, "\t<th>WFNS</th>\n");
    fprintf(fp, "\t<th>Treatment</th>\n");
    fprintf(fp, "</tr>\n");
    for (unsigned i = 0; i < nr_persons; ++i)
    {
        person_t p = *(list + i);
        fprintf(fp, "<tr>\n");
        fprintf(fp, "\t<td>%u</td>\n", i + 1);
        fprintf(fp, "\t<td>%u</td>\n", p.age);
        fprintf(fp, "\t<td>%c</td>\n", p.sex);
        fprintf(fp, "\t<td>%c</td>\n", p.hta);
        fprintf(fp, "\t<td>%c</td>\n", p.hsa);
        fprintf(fp, "\t<td>%c</td>\n", p.inc);
        fprintf(fp, "\t<td>%c</td>\n", (p.fisher == '-' ? p.fisher : p.fisher + 48));
        switch (p.glasg)
        {
            case NONE:
                fprintf(fp, "\t<td>--</td>\n");
                break;
            case LIGHT:
                fprintf(fp, "\t<td>Light</td>\n");
                break;
            case MODERATE:
                fprintf(fp, "\t<td>Moderate</td>\n");
                break;
            case SEVERE:
                fprintf(fp, "\t<td>Severe</td>\n");
                break;
        }
        fprintf(fp, "\t<td>%c</td>\n", (p.wfns == '-' ? p.wfns: p.wfns+ 48));
        fprintf(fp, "\t<td>%c</td>\n", p.treat);
        fprintf(fp, "</tr>\n");
    }

    html_fill_end(fp);

    fclose(fp);

    return 0;
}

void html_fill_header(FILE * fp)
{
    // First, the DOCTYPE
    fprintf(fp, "<!DOCTYPE html>\n");
    fprintf(fp, "<html>\n");
    fprintf(fp, "<head>\n<style>\n");
    fprintf(fp, "table {\n");
    fprintf(fp, "\tfont-family: arial, sans-serif;\n\tborder-collapse: collapse;\n\twidth: 100%%;\n}\n");
    fprintf(fp, "\ntd, th {\n");
    fprintf(fp, "\tborder: 1px solid #dddddd;\n\ttext-align: left;\n\tpadding: 8px;\n}\n");
    fprintf(fp, "\ntr:nth-child(even) {\n\tbackground-color: #dddddd;\n}\n");
    fprintf(fp, "</style>\n</head>\n");
    fprintf(fp, "<body>\n\n");
    fprintf(fp, "<h2>Patient list</h2>\n\n");
}

void html_fill_end(FILE * fp)
{
    fprintf(fp, "</table>\n\n");
    fprintf(fp, "</body>\n");
    fprintf(fp, "</html>\n");
}
