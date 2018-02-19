#include <stdio.h>
#include <stdarg.h>

#include "html.h"

#define     HTML_OUT_FILE   "html/patients.html"

int html_export(person_t * list, unsigned nr_persons, int min_age, int max_age)
{
    if (nr_persons == 0) return -1;

    FILE * fp = fopen(HTML_OUT_FILE, "w");

    if (!fp) return -1;

    html_fill_header(fp);

    html_set_fieldset(fp, nr_persons, min_age, max_age);

    html_fill_table(fp, list, nr_persons);

    html_add_scripts(fp);

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
    html_add_line(fp, "fieldset {");
    html_add_line(fp, "\twidth: 30%%;\n}");
    html_add_line(fp, "table {");
    html_add_line(fp, "\tfont-family: arial, sans-serif;\n\tborder-collapse: collapse;\n\twidth: 100%%;\n}");
    html_add_line(fp, "\ntd, th {");
    html_add_line(fp, "\tborder: 1px solid #dddddd;\n\ttext-align: left;\n\tpadding: 8px;\n}");
    html_add_line(fp, "tr:hover {background-color:#99ccff;}");
    html_add_line(fp, "</style>\n</head>");
    html_add_line(fp, "<body>");
    html_add_line(fp, "<h2>Patient list</h2>");
}

void html_fill_end(FILE * fp)
{
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

void html_set_fieldset(FILE * fp, unsigned nr_persons, int min_age, int max_age)
{
    html_add_line(fp, "<fieldset>");
    html_add_line(fp, "\t<legend>Filter parameters</legend>");

    html_add_line(fp, "\tAge: <select id=\"select_age\" >");
    html_add_line(fp, "\t\t<option value=\"none\">Select...</option>");
    for (int i = min_age; i <= max_age; ++i)
    {
        html_add_line(fp, "\t\t<option value=\"%d\">%d</option>", i, i);
    }
    html_add_line(fp, "\t</select><br>");

    html_add_line(fp, "\tSex: <select id=\"select_sex\" >");
    html_add_line(fp, "\t\t<option value=\"none\">Select...</option>");
    html_add_line(fp, "\t\t<option value=\"m\">Male</option>");
    html_add_line(fp, "\t\t<option value=\"f\">Female</option>");
    html_add_line(fp, "\t</select><br>");

    html_add_line(fp, "\tHTA: <select id=\"select_hta\" >");
    html_add_line(fp, "\t\t<option value=\"none\">Select...</option>");
    html_add_line(fp, "\t\t<option value=\"y\">Y</option>");
    html_add_line(fp, "\t\t<option value=\"n\">N</option>");
    html_add_line(fp, "\t</select><br>");

    html_add_line(fp, "\tHSA: <select id=\"select_hsa\" >");
    html_add_line(fp, "\t\t<option value=\"none\">Select...</option>");
    html_add_line(fp, "\t\t<option value=\"y\">Y</option>");
    html_add_line(fp, "\t\t<option value=\"n\">N</option>");
    html_add_line(fp, "\t</select><br>");

    html_add_line(fp, "\tIncidental: <select id=\"select_inc\" >");
    html_add_line(fp, "\t\t<option value=\"none\">Select...</option>");
    html_add_line(fp, "\t\t<option value=\"y\">Y</option>");
    html_add_line(fp, "\t\t<option value=\"n\">N</option>");
    html_add_line(fp, "\t</select><br>");

    html_add_line(fp, "\tFisher: <select id=\"select_fisher\" >");
    html_add_line(fp, "\t\t<option value=\"none\">Select...</option>");
    for (int i = 0; i < 5; ++i)
    {
        char n[2];
        sprintf(n, "%d", i);
        n[1] = '\0';
        html_add_line(fp, "\t\t<option value=\"%s\">%s</option>",
                (i == 0 ? "-" : n),
                (i == 0 ? "--" : n));
    }
    html_add_line(fp, "\t</select><br>");

    html_add_line(fp, "\tGlasgow: <select id=\"select_glasgow\" >");
    html_add_line(fp, "\t\t<option value=\"none\">Select...</option>");
    html_add_line(fp, "\t\t<option value=\"--\">--</option>");
    html_add_line(fp, "\t\t<option value=\"light\">light</option>");
    html_add_line(fp, "\t\t<option value=\"moderate\">moderate</option>");
    html_add_line(fp, "\t\t<option value=\"severe\">severe</option>");
    html_add_line(fp, "\t</select><br>");

    html_add_line(fp, "\tWFNS: <select id=\"select_wfns\" >");
    html_add_line(fp, "\t\t<option value=\"none\">Select...</option>");
    for (int i = 0; i < 6; ++i)
    {
        char n[2];
        n[1] = '\0';
        sprintf(n, "%d", i);
        html_add_line(fp, "\t\t<option value=\"%s\">%s</option>",
                (i == 0 ? "--" : n),
                (i == 0 ? "--" : n));
    }
    html_add_line(fp, "\t</select><br>");

    html_add_line(fp, "\tTreatment: <select id=\"select_treat\" >");
    html_add_line(fp, "\t\t<option value=\"none\">Select...</option>");
    html_add_line(fp, "\t\t<option value=\"a\">A</option>");
    html_add_line(fp, "\t\t<option value=\"b\">B</option>");
    html_add_line(fp, "\t</select><br>");

    html_add_line(fp, "\t<button type=\"button\" onclick=\"setFilters()\">Apply filters</button>");
    html_add_line(fp, "\t<button type=\"button\" onclick=\"clearFilters()\">Clear filters</button>");

    html_add_line(fp, "<p id=\"nr_patients\">Number of patients: %d</p>", nr_persons);
    html_add_line(fp, "</fieldset><br>");
}

void html_fill_table(FILE * fp, person_t * list, unsigned nr_persons)
{
    // Enter a new entry with the information in the list
    html_add_line(fp, "<table id=\"patientTable\">");
    html_add_line(fp, "<colgroup>");
    for (int i = 0; i < 10; ++i)
    {
        html_add_line(fp, "\t<col id=\"c%d\">", i);
    }
    html_add_line(fp, "</colgroup>");
    html_add_line(fp, "<tr>");
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
    html_add_line(fp, "</table>");
}

void html_add_scripts(FILE * fp)
{
    html_add_line(fp, "<script>");
    html_add_line(fp, "function setFilters() {\n");
    html_add_line(fp, "\tvar filter_age, filter_sex, filter_hta, filter_hsa, filter_inc, filter_fisher, filter_glasgow, filter_wfns, filter_treat;");
    html_add_line(fp, "\tvar td, td1, td2, td3, td4, td5, td6, td7, td8, td9;");
    html_add_line(fp, "\tvar table, tr, td, i, n;\n");
    html_add_line(fp, "\tfilter_age = document.getElementById(\"select_age\").value.toUpperCase();");
    html_add_line(fp, "\tfilter_sex = document.getElementById(\"select_sex\").value.toUpperCase();");
    html_add_line(fp, "\tfilter_hta = document.getElementById(\"select_hta\").value.toUpperCase();");
    html_add_line(fp, "\tfilter_hsa = document.getElementById(\"select_hsa\").value.toUpperCase();");
    html_add_line(fp, "\tfilter_inc = document.getElementById(\"select_inc\").value.toUpperCase();");
    html_add_line(fp, "\tfilter_fisher = document.getElementById(\"select_fisher\").value.toUpperCase();");
    html_add_line(fp, "\tfilter_glasgow = document.getElementById(\"select_glasgow\").value.toUpperCase();");
    html_add_line(fp, "\tfilter_wfns = document.getElementById(\"select_wfns\").value.toUpperCase();");
    html_add_line(fp, "\tfilter_treat = document.getElementById(\"select_treat\").value.toUpperCase();\n");
    html_add_line(fp, "\t// Color columns with the given search parameters");
    html_add_line(fp, "\tif (filter_age != \"NONE\") {\n\t\tdocument.getElementById(\"c1\").style = \"background-color: #ff9966;\";\n\t}");
    html_add_line(fp, "\tif (filter_sex != \"NONE\") {\n\t\tdocument.getElementById(\"c2\").style = \"background-color: #ff9966;\";\n\t}");
    html_add_line(fp, "\tif (filter_hta != \"NONE\") {\n\t\tdocument.getElementById(\"c3\").style = \"background-color: #ff9966;\";\n\t}");
    html_add_line(fp, "\tif (filter_hsa != \"NONE\") {\n\t\tdocument.getElementById(\"c4\").style = \"background-color: #ff9966;\";\n\t}");
    html_add_line(fp, "\tif (filter_inc != \"NONE\") {\n\t\tdocument.getElementById(\"c5\").style = \"background-color: #ff9966;\";\n\t}");
    html_add_line(fp, "\tif (filter_fisher != \"NONE\") {\n\t\tdocument.getElementById(\"c6\").style = \"background-color: #ff9966;\";\n\t}");
    html_add_line(fp, "\tif (filter_glasgow != \"NONE\") {\n\t\tdocument.getElementById(\"c7\").style = \"background-color: #ff9966;\";\n\t}");
    html_add_line(fp, "\tif (filter_wfns != \"NONE\") {\n\t\tdocument.getElementById(\"c8\").style = \"background-color: #ff9966;\";\n\t}");
    html_add_line(fp, "\tif (filter_treat != \"NONE\") {\n\t\tdocument.getElementById(\"c9\").style = \"background-color: #ff9966;\";\n\t}");

    html_add_line(fp, "\ttable = document.getElementById(\"patientTable\");");
    html_add_line(fp, "\ttr = table.getElementsByTagName(\"tr\");\n");
    html_add_line(fp, "\t// Init number of patients\n\tn = 0;");

    html_add_line(fp, "\tfor (i = 0; i < tr.length; i++) {");
    html_add_line(fp, "\t\ttd = tr[i].getElementsByTagName(\"td\")[1];");
    html_add_line(fp, "\t\ttd2= tr[i].getElementsByTagName(\"td\")[2];");
    html_add_line(fp, "\t\ttd3= tr[i].getElementsByTagName(\"td\")[3];");
    html_add_line(fp, "\t\ttd4= tr[i].getElementsByTagName(\"td\")[4];");
    html_add_line(fp, "\t\ttd5= tr[i].getElementsByTagName(\"td\")[5];");
    html_add_line(fp, "\t\ttd6= tr[i].getElementsByTagName(\"td\")[6];");
    html_add_line(fp, "\t\ttd7= tr[i].getElementsByTagName(\"td\")[7];");
    html_add_line(fp, "\t\ttd8= tr[i].getElementsByTagName(\"td\")[8];");
    html_add_line(fp, "\t\ttd9= tr[i].getElementsByTagName(\"td\")[9];");
    html_add_line(fp, "\t\tif (td && td2 && td3 && td4 && td5 && td6 && td7 && td8 && td9) {");
    html_add_line(fp, "\t\t\tif ((td.innerHTML.toUpperCase().indexOf(filter_age) > -1 || filter_age == \"NONE\") &&");
    html_add_line(fp, "\t\t\t\t(td2.innerHTML.toUpperCase().indexOf(filter_sex) > -1 || filter_sex == \"NONE\") &&");
    html_add_line(fp, "\t\t\t\t(td3.innerHTML.toUpperCase().indexOf(filter_hta) > -1 || filter_hta == \"NONE\") &&");
    html_add_line(fp, "\t\t\t\t(td4.innerHTML.toUpperCase().indexOf(filter_hsa) > -1 || filter_hsa == \"NONE\") &&");
    html_add_line(fp, "\t\t\t\t(td5.innerHTML.toUpperCase().indexOf(filter_inc) > -1 || filter_inc == \"NONE\") &&");
    html_add_line(fp, "\t\t\t\t(td6.innerHTML.toUpperCase().indexOf(filter_fisher) > -1 || filter_fisher == \"NONE\") &&");
    html_add_line(fp, "\t\t\t\t(td7.innerHTML.toUpperCase().indexOf(filter_glasgow) > -1 || filter_glasgow == \"NONE\") &&");
    html_add_line(fp, "\t\t\t\t(td8.innerHTML.toUpperCase().indexOf(filter_wfns) > -1 || filter_wfns == \"NONE\") &&");
    html_add_line(fp, "\t\t\t\t(td9.innerHTML.toUpperCase().indexOf(filter_treat) > -1 || filter_treat == \"NONE\")) {");
    html_add_line(fp, "\t\t\t\ttr[i].style.display = \"\";");
    html_add_line(fp, "\t\t\t\tn++;");
    html_add_line(fp, "\t\t\t} else {");
    html_add_line(fp, "\t\t\t\ttr[i].style.display = \"none\";\n\t\t\t}\n\t\t}\n\t}");
    html_add_line(fp, "\tdocument.getElementById(\"nr_patients\").innerHTML = \"Number of patients: \" + n + \" (\" + (100 * n / (tr.length - 1)).toFixed(2) + \" %)\";\n}\n");

    html_add_line(fp, "function clearFilters() {\n");
    html_add_line(fp, "\tvar table, tr, td, i;");
    html_add_line(fp, "\ttable = document.getElementById(\"patientTable\");");
    html_add_line(fp, "\ttr = table.getElementsByTagName(\"tr\");\n");
    html_add_line(fp, "\tfor (i = 0; i < tr.length; i++) {");
    html_add_line(fp, "\t\ttr[i].style.display = \"\";");
    html_add_line(fp, "\t}\n\t// Reset filter prompts");
    html_add_line(fp, "\tdocument.getElementById(\"select_age\").value = \"none\";");
    html_add_line(fp, "\tdocument.getElementById(\"select_sex\").value = \"none\";");
    html_add_line(fp, "\tdocument.getElementById(\"select_hta\").value = \"none\";");
    html_add_line(fp, "\tdocument.getElementById(\"select_hsa\").value = \"none\";");
    html_add_line(fp, "\tdocument.getElementById(\"select_inc\").value = \"none\";");
    html_add_line(fp, "\tdocument.getElementById(\"select_fisher\").value = \"none\";");
    html_add_line(fp, "\tdocument.getElementById(\"select_glasgow\").value = \"none\";");
    html_add_line(fp, "\tdocument.getElementById(\"select_wfns\").value = \"none\";");
    html_add_line(fp, "\tdocument.getElementById(\"select_treat\").value = \"none\";");
    html_add_line(fp, "\t// Reset column coloring");
    html_add_line(fp, "\tdocument.getElementById(\"c1\").style = \"background-color: #ffffff;\";");
    html_add_line(fp, "\tdocument.getElementById(\"c2\").style = \"background-color: #ffffff;\";");
    html_add_line(fp, "\tdocument.getElementById(\"c3\").style = \"background-color: #ffffff;\";");
    html_add_line(fp, "\tdocument.getElementById(\"c4\").style = \"background-color: #ffffff;\";");
    html_add_line(fp, "\tdocument.getElementById(\"c5\").style = \"background-color: #ffffff;\";");
    html_add_line(fp, "\tdocument.getElementById(\"c6\").style = \"background-color: #ffffff;\";");
    html_add_line(fp, "\tdocument.getElementById(\"c7\").style = \"background-color: #ffffff;\";");
    html_add_line(fp, "\tdocument.getElementById(\"c8\").style = \"background-color: #ffffff;\";");
    html_add_line(fp, "\tdocument.getElementById(\"c9\").style = \"background-color: #ffffff;\";");
    html_add_line(fp, "\tdocument.getElementById(\"nr_patients\").innerHTML = \"Number of patients: \" + (tr.length - 1);");
    html_add_line(fp, "}");

    html_add_line(fp, "</script>");
}
