//
//  main.cpp
//  data-structure-course
//
//  Created by Zahir Gudiño on 1/21/16.
//  Copyright © 2016 Zahir Gudiño. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

float calcextra(int*, float&);
float calcgross(int*, float&);
float calcnet(float&);
string firstupper(string&);

const int LE_HOURS = 40; // horas base
const float X_RATE_PERC = 0.15; // % horas extras
const float A_DISC_PERC = 0.20; // % descuento grupo A
const float B_DISC_PERC = 0.10; // % descuento grupo B

/* Estructura empleado */
struct Employee {
    string name;
    int age, hoursWorked;
    float ratePerHour, extraSalary, grossSalary, netSalary;
};

int main(int argc, const char * argv[]) {
    Employee employee[3]; // empleados
    Employee empbp; // objeto empleado mejor pagado
    
    int count = 0;
    
    cout << "DUMMY PAYROLL (ver.1)" << endl;
    cout << endl;
    
    /* Iterar cada uno de los objectos employee */
    for(auto& emp: employee) { // emp refiere al objeto actual de la coleccion de objetos employee
        cout << "Empleado #" << ++count;
        cout << "\n";
        
        cout << "Nombre: "; cin >> emp.name;
        cout << "Edad: "; cin >> emp.age;
        cout << "Rata (salario/hora): "; cin >> emp.ratePerHour;
        cout << "Horas: "; cin >> emp.hoursWorked;
        
        emp.extraSalary = calcextra(&emp.hoursWorked, emp.ratePerHour); // salario bruto
        /**
         Salario bruto no contempla salario extra, emp.extraSalary.
         Si en su implementacion necesita contemplar extras, solamente basta con sumar emp.extraSalary.
         
         El siguiente ejemplo sumar el resultado de la funcion + salario extra.
         Ejemplo,
            emp.grossSalary = calcgross(&emp.hoursWorked, emp.ratePerHour) + emp.extraSalary;
         
         Note que agregar emp.extraSalary afecta el resultado de salario neto.
         */
        emp.grossSalary = calcgross(&emp.hoursWorked, emp.ratePerHour);
        emp.netSalary = calcnet(emp.grossSalary); // salario neto
        
        /* Aprovechamos el cliclo para asignar a otro objeto empleado con mejor salario neto */
        if (emp.netSalary > empbp.netSalary)
            empbp = emp; // asignamos objeto emp a empbp
        
        cout << "\n\n";
    }
    
    cout << "Empleado " << firstupper(empbp.name) << ", de " << empbp.age << " años de edad, tiene mejor salario. ($" << empbp.netSalary << ")";
    cout << endl;
    
    return 0;
}

/**
 *  Calcula horas extras
 *
 *  @param hours     Horas laboradas
 *  @param rate_hour Rata (salario/hora)
 *
 *  @return extras Salario extra calculado
 */
float calcextra(int* hrs, float& rate_hr) {
    float extras = 0;
    
    /* Horas laboradas >40
     Formula para calcular las horas extras >> horas_extras * ((rata_por_hora * XRP) + rata_por_hora)
     */
    if (*hrs > 40)
        extras = (*hrs - LE_HOURS) * ((rate_hr * X_RATE_PERC) + rate_hr);
    
    return extras;
}

/**
 *  Calcula salario bruto
 *
 *  @param hrs     Horas laboradas
 *  @param rate_hr Rata (salario/hora)
 *
 *  @return Salario bruto calculado
 */
float calcgross(int* hrs, float& rate_hr) {
    int base_hrs = (*hrs > 40) ? *hrs - (*hrs - LE_HOURS) : *hrs;
    float gsal = base_hrs * rate_hr;
    
    return gsal;
}

/**
 *  Calcula salario neto
 *
 *  @param gross Salario bruto
 *
 *  @return Salario neto calculado
 */
float calcnet(float& gross) {
    float nsal = 0;
    
    if (gross > 600) {
        nsal = gross - (gross * A_DISC_PERC);
    }
    else if (gross > 399.99 && gross < 600) {
        nsal = gross - (gross * B_DISC_PERC);
    }
    else {
        nsal = gross;
    }
    
    return nsal;
}

/**
 *  Mayuscula primera letra de una cadena
 *
 *  @param str Cadena entrada
 *
 *  @return Retorna una nueva cadena con la primera letra mayuscula
 */
string firstupper(string& str) {
    string s = str;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    
    if (! s.empty()) {
        s[0] = toupper(s[0]);
    }
    
    return s;
}
