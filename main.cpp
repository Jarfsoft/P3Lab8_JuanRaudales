#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>
//7
using namespace std;

int main(int argc, char** argv)
{
	sqlite3 *conn;
	sqlite3_stmt *res;
	int error=0;
	int rec_count=0;
	const char *tail;
	
	int opcion=0;
	while(opcion!=7)
	{
		cout<<"**********Base de datos************\n\n1.Listar\n2.Agregar\n3.Eliminar\n4.Listar jefe y empleado\n5.Actualizar salario empleado\n6.Empleados de departamento\n7.Salir\n\nSeleccion: ";
		cin>>opcion;
		if(opcion==1)
		{
			error=sqlite3_open("oracle-sample.db", &conn);
			
			if(error ==1)
			{
				cout<<"Error abriendo archivo"<<endl;
				return 0;
			}
			error=sqlite3_prepare_v2(conn, "select * from emp",1000,&res,&tail);
			cout<<"Empleados: "<<"\n\n";
			while(sqlite3_step(res) == SQLITE_ROW)
			{
				cout<<sqlite3_column_text(res,0)<<", ";
				cout<<sqlite3_column_text(res,1)<<", ";
				cout<<sqlite3_column_text(res,2)<<", ";
				cout<<sqlite3_column_text(res,3)<<", ";
				cout<<sqlite3_column_text(res,4)<<", ";
				cout<<sqlite3_column_text(res,5)<<", ";
				cout<<sqlite3_column_text(res,6)<<", ";
				cout<<sqlite3_column_text(res,7)<<endl;
			}
			cout<<"\n\n";
			
			error=sqlite3_prepare_v2(conn, "select * from dept",1000,&res,&tail);
			
			cout<<"Departamentos: "<<"\n\n";
			while(sqlite3_step(res) == SQLITE_ROW)
			{
				cout<<sqlite3_column_text(res,0)<<", ";
				cout<<sqlite3_column_text(res,1)<<", ";
				cout<<sqlite3_column_text(res,2)<<endl;
			}
			
			sqlite3_close(conn);
		}
		if(opcion==2)
		{
			cout<<"\n\n1.Empleado\n2.Departamento\n\nSeleccion: ";
			cin>>opcion;
			if(opcion==1)
			{
				string numero, nombre, trabajo, mgr, fecha, salario, comm, departamento;
				cout<<"\n\nNumero de empleado: ";
				cin>>numero;
				cout<<"Nombre de empleado: ";
				cin>>nombre;
				cout<<"Trabajo: ";
				cin>>trabajo;
				cout<<"Jefe: ";
				cin>>mgr;
				cout<<"Fecha de contratacion: ";
				cin>>fecha;
				cout<<"Salario: ";
				cin>>salario;
				cout<<"Comm: ";
				cin>>comm;
				cout<<"Departamento: ";
				cin>>departamento;
				string query="insert into emp values('"+numero+"','"+nombre+"','"+trabajo+"','"+mgr+"','"+fecha+"','"+salario+"','"+comm+"','"+departamento+"')";
				error=sqlite3_open("oracle-sample.db",&conn);
				error=sqlite3_exec(conn,
				query.c_str()
				,0,0,0);
				sqlite3_close(conn);
				if(error!=SQLITE_OK)
				{
					cout<<"\n\nHubo un error en el proceso.\n\n";
				}
				else
					cout<<"\n\nEmpleado agregado con exito.\n\n";
			}
			if(opcion==2)
			{
				string numero, nombre, localidad;
				cout<<"\n\nNumero de departamento: ";
				cin>>numero;
				cout<<"Nombre del departamento: ";
				cin>>nombre;
				cout<<"Localidad: ";
				cin>>localidad;
				string query="insert into dept values('"+numero+"','"+nombre+"','"+localidad+"')";
				error=sqlite3_open("oracle-sample.db",&conn);
				error=sqlite3_exec(conn,
				query.c_str()
				,0,0,0);
				sqlite3_close(conn);
				if(error!=SQLITE_OK)
				{
					cout<<"\n\nHubo un error en el proceso.\n\n";
				}
				else
					cout<<"\n\nEmpleado agregado con exito.\n\n";
			}
			opcion=0;
		}
		if(opcion==3)
		{
			string numero;
			cout<<"\n\nNumero de empleado: ";
			cin>>numero;
			string query="delete from emp where empno='"+numero+"'";
			error=sqlite3_open("oracle-sample.db",&conn);
			error=sqlite3_exec(conn,
			query.c_str()
			,0,0,0);
			sqlite3_close(conn);
			if(error!=SQLITE_OK)
			{
				cout<<"\n\nHubo un error en el proceso.\n\n";
			}
			else
				cout<<"\n\nEmpleado agregado con exito.\n\n";
		}
		if(opcion==4)
		{
			
			error=sqlite3_open("oracle-sample.db", &conn);
			
			if(error ==1)
			{
				cout<<"Error abriendo archivo"<<endl;
				return 0;
			}
			
			string numero;
			cout<<"\n\nNumero de empleado: ";
			cin>>numero;
			string query="select * from emp where empno='"+numero+"'";
			error=sqlite3_prepare_v2(conn, query.c_str(),1000,&res,&tail);
			if(error!=SQLITE_OK)
			{
				cout<<"\n\nHubo un error en el proceso.\n\n";
				return 0;
			}
			if(sqlite3_step(res) == SQLITE_ROW){
				cout<<"Jefe:\n"<<sqlite3_column_text(res,1)<<"\n\nEmpleados:\n";
				query="select * from emp where mgr='"+numero+"'";
				error=sqlite3_prepare_v2(conn, query.c_str(),query.size()+1,&res,&tail);
				while(sqlite3_step(res) == SQLITE_ROW)
				{
					cout<<sqlite3_column_text(res,0)<<", ";
					cout<<sqlite3_column_text(res,1)<<", ";
					cout<<sqlite3_column_text(res,2)<<", ";
					cout<<sqlite3_column_text(res,3)<<", ";
					cout<<sqlite3_column_text(res,4)<<", ";
					cout<<sqlite3_column_text(res,5)<<", ";
					cout<<sqlite3_column_text(res,6)<<", ";
					cout<<sqlite3_column_text(res,7)<<endl;
				}
				
			}else{
				cout<< "No enontro ese empleado" << endl;
			}	
			
		}
		if(opcion==5)
		{
			string numero, salario;
			int sal=0;
			int cont=0;
			cout<<"\n\nNumero de empleado: ";
			cin>>numero;
			string query="select * from emp where mgr='"+numero+"'";
			error=sqlite3_prepare_v2(conn, query.c_str(),query.size()+1,&res,&tail);
			while(sqlite3_step(res) == SQLITE_ROW)
			{
				string temp = (char*)sqlite3_column_text(res,5);
				sal+=atoi(temp.c_str());
				cont++;
			}
			sal/=cont;
			sal*=2;
			char temp[10];
			itoa(sal,temp,10);
			salario=temp;
			query="update emp set sal='"+salario+"' where empno='"+numero+"'";
			error=sqlite3_open("oracle-sample.db",&conn);
			error=sqlite3_exec(conn,
			query.c_str()
			,0,0,0);
			if(error!=SQLITE_OK)
			{
				cout<<"\n\nHubo un error en el proceso.\n\n";
			}
			else
				cout<<"\n\nSalario actualizado con exito.\n\n";
			sqlite3_close(conn);
		}
		if(opcion==6)
		{
			error=sqlite3_open("oracle-sample.db", &conn);
			
			if(error ==1)
			{
				cout<<"Error abriendo archivo"<<endl;
				return 0;
			}
			
			string numero;
			cout<<"\n\nNumero de departamento: ";
			cin>>numero;
			string query="select * from dept where deptno='"+numero+"'";
			error=sqlite3_prepare_v2(conn, query.c_str(),query.size()+1,&res,&tail);
			if(error!=SQLITE_OK)
			{
				cout<<"\n\nHubo un error en el proceso.\n\n";
				return 0;
			}
			if(sqlite3_step(res) == SQLITE_ROW){
				cout<<"Departamento:\n"<<sqlite3_column_text(res,1)<<"\n\nEmpleados:\n";
				query="select * from emp where deptno='"+numero+"'";
				error=sqlite3_prepare_v2(conn, query.c_str(),query.size()+1,&res,&tail);
				while(sqlite3_step(res) == SQLITE_ROW)
				{
					cout<<sqlite3_column_text(res,0)<<", ";
					cout<<sqlite3_column_text(res,1)<<", ";
					cout<<sqlite3_column_text(res,2)<<", ";
					cout<<sqlite3_column_text(res,3)<<", ";
					cout<<sqlite3_column_text(res,4)<<", ";
					cout<<sqlite3_column_text(res,5)<<", ";
					cout<<sqlite3_column_text(res,6)<<", ";
					cout<<sqlite3_column_text(res,7)<<endl;
				}
				
			}else{
				cout<< "No enontro ese empleado" << endl;
			}	
		}
	}
		
	
	
	
	return 0;
}
