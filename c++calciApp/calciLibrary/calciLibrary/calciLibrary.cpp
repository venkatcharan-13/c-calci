#include "pch.h"
#include "calciLibrary.h"

using namespace std;


//declaring the universal variables
const char* conninfo = "host=localhost port=5432 dbname=test user=postgres password=ccccc";
string st = "";
int temp=0;

//defining all the functions 

string changeToString(int a, int b, char si) {
	string signstr = "";
	if (si == '+') { signstr = "+"; }
	else if(si=='-') { signstr = "-"; }
	else if(si=='*') { signstr = "*"; }
	else { signstr = "/"; }
	string innertemp = "";
	innertemp += to_string(a) + signstr + to_string(b);
	return innertemp;
}
void display_outputInt(int answer)
{
	cout << "-----------------------------------------" << endl;
	cout << "| The answer is :             "<<answer   << endl;
	cout << "-----------------------------------------" << endl;

}
void display_outputLli(long long int  answer)
{
	cout << "-----------------------------------------" << endl;
	cout << "| The answer is :            " << answer  << endl;
	cout << "-----------------------------------------" << endl;

}
void display_outputLd(long double  answer)
{
	cout << "-----------------------------------------" << endl;
	cout << "| The answer is :            " << answer << endl;
	cout << "-----------------------------------------" << endl;

}
void calci::commonFunc(int a, int b,char si) {
	st = changeToString(a, b, si);
	temp = 0;
	if (si == '+') {
		temp = a + b;
	}
	else if (si == '-') {
		temp = a - b;
	}
	else if (si == '*') {
		temp = a * b;
	}
	else {
		temp = a / b;
	}
	InsertData(st, to_string(temp));
	display_outputInt(temp);
}
void calci::trinoFunc(int degree, string function) {
	long double  x = degree * 3.14159 / 180;
	long double Ntemp = 0.0;
	if (function == "sine") {
		st = "sin(";
		Ntemp =sin(x);
	}
	else if (function == "cos") {
		st = "cos(";
		Ntemp = cos(x);
	}
	else if (function == "tan") {
		st = "tan(";
		Ntemp = tan(x);
	}

	InsertData((st + to_string(degree) + ")"), to_string(Ntemp));
	display_outputLd(Ntemp);
}

void calci::logFunc(int n,int base) {
	long double nTemp = 0.0;
	if (base == 2) {
		st = "log2 of";
		nTemp = log2(n);
	}
	else if (base == 10) {
		st = "log10 of";
		nTemp = log10(n);
	}
	InsertData(st+to_string(n), to_string(nTemp));
	display_outputLd(nTemp);
}

void calci::powFunc(int n, int power,char bse) {
	long long int pw = 0;
	if (bse == 'e') {
		st = "e to the power of ";
		pw = exp(n);
	}else {
		st = to_string(n) + " to the power of" + to_string(power);
		pw = pow(n, power);
	}
	InsertData(st, to_string(pw));
	display_outputLli(pw);
}
string meanstr(vector<int>array,int n,string mode) {
	string res = mode+" "+" { ";
	for (int i = 0; i < n; i++) {
		res +="  " + to_string(array[i]);
	}
	res += " }";
	return res;
}
void calci::meanFunc(vector<int>array, string common) {
	int n = array.size();
	long double nTemp = 0.0;
	if (common == "mean") {
		long double sm = 0.0;
		for (int i = 0; i < n; i++) {
			sm += (long double) array[i];
		}
		nTemp = sm / (long double) n;
	}
	else if (common == "median") {
		sort(array.begin(), array.end());
		if ((n % 2 == 0)) {
			nTemp = ((long double) array[n / 2 - 1] + (long double) array[n / 2]) / 2.0;
		}
		else {
			nTemp = (long double) array[n / 2];
		}
	}
	InsertData(meanstr(array, n, common), to_string(nTemp));
	display_outputLd(nTemp);
}

void calci::stdDeviation(vector<int>data) {
	int n =data.size();
	long double m=0.0;
	for (int i = 0; i < n; i++) {
		m += (long double)data[i]; 
	}
	m /= (long double) n;
	long double sumOfSquares = 0;
	for (int value : data) {
		sumOfSquares += pow((long double) value - m, 2);
	}
	InsertData(meanstr(data, n, "Standard Deviation"),to_string(sqrt(sumOfSquares / (long double) n)));
	display_outputLd(sqrt(sumOfSquares / (long double) n));
}
void calci::showCalci() {
	cout << "-----------------------------------------" << endl;
	cout << "----                                  ---" << endl;
	cout << "-             SCIENTIFIC                -" << endl;
	cout << "-             CALCULATOR                -" << endl;
	cout << "---                                   ---" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "-      +     |      -      |      *     -" << endl;
	cout << "-     Add    |    Minus    |  Multiply  -" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "-      /     |      A      |      B     -" << endl;
	cout << "-   Divide   |     Log10   |     Log2   -" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "-      C     |      D      |      E     -" << endl;
	cout << "-    Square  |    Power    |     exp    -" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "-      F     |      G      |      H     -" << endl;
	cout << "-     sin    |     cos     |     tan    -" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "-     I      |      J      |     K      -" << endl;
	cout << "-    mean    |   median    |   stdDiv   -" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "-           press . to exit             -" << endl;
	cout << "-----------------------------------------" << endl;
}
void CheckResult(PGresult* res, PGconn* conn) {
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		std::cerr << "Error: " << PQerrorMessage(conn) << std::endl;
		PQclear(res);
		PQfinish(conn);
		exit(1);
	}
}
void createTable(PGconn* conn) {
    const char* sql =
        "CREATE TABLE IF NOT EXISTS datatable ("
        "inputcol TEXT,"
        "outputcol TEXT,"
        "timestampcol TEXT"
        ");";
    PGresult* res = PQexec(conn, sql);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "CREATE TABLE command failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        return;
    }
    cout << "Table created successfully!" << std::endl;
    PQclear(res);
}

void InsertData(string col1, string col2) {
	PGconn* conn = PQconnectdb(conninfo);
	if (PQstatus(conn) != CONNECTION_OK) {
		std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
		PQfinish(conn);
		return;
	}
	//timestamp;
	auto now = chrono::system_clock::now();
	time_t now_c = chrono::system_clock::to_time_t(now);
	tm local_tm;
#ifdef _MSC_VER
	localtime_s(&local_tm, &now_c);
#else
	local_tm = *std::localtime(&now_c);
#endif
	ostringstream oss;
	oss << put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
	string timestamp = oss.str();

	if (CountRows(conn, "datatable")>=50) {
		DeleteAllRows(conn, "datatable");
	}
	const char* paramValues[3] = { col1.c_str(),col2.c_str(),timestamp.c_str() };
	PGresult* res = PQexecParams(conn,
		"INSERT INTO datatable (inputcol,outputcol,timestampcol) VALUES ($1,$2,$3)",
		3, NULL, paramValues, NULL, NULL, 0
	);

	CheckResult(res, conn);
	//cout << "data is inserted!!" << endl;
	PQclear(res);
	PQfinish(conn);
}

int CountRows(PGconn* conn,string tableName) {
	if (!conn) {
		std::cerr << "Invalid connection object." << std::endl;
		return -1;
	}
	string sql = "SELECT COUNT(*) FROM ";
	sql += tableName;
	sql += ";";
	PGresult* res = PQexec(conn, sql.c_str());

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		std::cerr << "COUNT query failed: " << PQerrorMessage(conn) << std::endl;
		PQclear(res);
		return -1;
	}

	int rowCount = stoi(PQgetvalue(res, 0, 0));

	PQclear(res);

	return rowCount;
}

void DeleteAllRows(PGconn* conn,string tableName) {
	if (!conn) {
		std::cerr << "Invalid connection object." << std::endl;
		return;
	}

	string sql = "DELETE FROM ";
	sql += tableName;
	sql += ";";

	PGresult* res = PQexec(conn, sql.c_str());

	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		std::cerr << "DELETE command failed: " << PQerrorMessage(conn) << std::endl;
		PQclear(res);
		return;
	}

	//cout << "All rows deleted successfully from table '" << tableName << "'." << std::endl;
	PQclear(res);
}










