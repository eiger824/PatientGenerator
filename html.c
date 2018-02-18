#include <stdio.h>
#include <stdarg.h>

#include "html.h"

#define     HTML_OUT_FILE   "html/patients.html"

int html_export(person_t * list, unsigned nr_persons)
{
    if (nr_persons == 0) return -1;

    FILE * fp = fopen(HTML_OUT_FILE, "w");

    if (!fp) return -1;

    html_fill_header(fp);

    // Enter a new entry with the information in the list
    html_add_line(fp, "<table>\n<tr>");
    html_add_line(fp, "\t<th>Patient</th>");
    html_add_line(fp, "\t<th>Age</th>");
    html_add_line(fp, "\t<th>Sex</th>");
    html_add_line(fp, "\t<th>HTA</th>");
    html_add_line(fp, "\t<th>HSA</th>");
    html_add_line(fp, "\t<th>Incident</th>");
    html_add_line(fp, "\t<th>Fisher</th>");
    html_add_line(fp, "\t<th>Glasgow</th>");
    html_add_line(fp, "\t<th>WFNS</th>");
    html_add_line(fp, "\t<th>Treatment</th>");
    html_add_line(fp, "</tr>");

    for (unsigned i = 0; i < nr_persons; ++i)
    {
        person_t p = *(list + i);
        html_add_line(fp, "<tr>");
        html_add_line(fp, "\t<td>%u</td>", i + 1);
        html_add_line(fp, "\t<td>%u</td>", p.age);
        html_add_line(fp, "\t<td>%c</td>", p.sex);
        html_add_line(fp, "\t<td>%c</td>", p.hta);
        html_add_line(fp, "\t<td>%c</td>", p.hsa);
        html_add_line(fp, "\t<td>%c</td>", p.inc);
        html_add_line(fp, "\t<td>%c</td>", (p.fisher == '-' ? p.fisher : p.fisher + 48));
        switch (p.glasg)
        {
            case NONE:
                html_add_line(fp, "\t<td>--</td>");
                break;
            case LIGHT:
                html_add_line(fp, "\t<td>Light</td>");
                break;
            case MODERATE:
                html_add_line(fp, "\t<td>Moderate</td>");
                break;
            case SEVERE:
                html_add_line(fp, "\t<td>Severe</td>");
                break;
        }
        html_add_line(fp, "\t<td>%c</td>", (p.wfns == '-' ? p.wfns: p.wfns+ 48));
        html_add_line(fp, "\t<td>%c</td>", p.treat);
        html_add_line(fp, "</tr>");
    }

    html_fill_end(fp);

    fclose(fp);

    return 0;
}

void html_fill_header(FILE * fp)
{
    // First, the DOCTYPE
    html_add_line(fp, "<!DOCTYPE html>");
    html_add_line(fp, "<html>");
    html_add_line(fp, "<head>\n<style>");
    html_add_line(fp, "table {");
    html_add_line(fp, "\tfont-family: arial, sans-serif;\n\tborder-collapse: collapse;\n\twidth: 100%%;\n}");
    html_add_line(fp, "\ntd, th {");
    html_add_line(fp, "\tborder: 1px solid #dddddd;\n\ttext-align: left;\n\tpadding: 8px;\n}");
    html_add_line(fp, "\ntr:nth-child(even) {\n\tbackground-color: #dddddd;\n}");
    html_add_line(fp, "</style>\n</head>");
    html_add_line(fp, "<body>");
    html_add_line(fp, "<h2>Patient list</h2>");
}

void html_fill_end(FILE * fp)
{
    html_add_line(fp, "</table>");
    html_add_line(fp, "</body>");
    html_add_line(fp, "</html>");
}

void html_add_line(FILE * fp, const char * msg, ...)
{
    va_list args;
    va_start(args, msg);
    vfprintf(fp, msg, args);
    fprintf(fp, "\n");
    va_end(args);
}
