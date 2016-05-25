#include "./FTP.h"

// Public

FTP::FTP(string host, string port, string user, string password){
  this->pi.connect(host, port);
  this->user = user;
  this->password = password;

  setUp();
};

FTP::~FTP(){

};

void FTP::execute(string message){

  vector<string> params = StringUtils::splitByDelimiter(message, ' ');
  string command = params[0];
  transform(command.begin(), command.end(), command.begin(), ::toupper);

  if ( command.compare("PWD") == 0 ){
    cout << this->pi.commandPrintWorkingDirectory();
  } else if ( command.compare("DELE") == 0 ){
    cout << this->pi.commandDeleteFile(params[1]);
  } else if ( command.compare("RMD") == 0 ){
    cout << this->pi.commandDeleteDir(params[1]);
  } else if ( command.compare("MKD") == 0 ){
    cout << this->pi.commandMakeDir(params[1]);
  } else if ( command.compare("HELP") == 0 ){
    cout << this->pi.commandHelp();
  } else if ( command.compare("CWD") == 0 ){
    cout << this->pi.commandChangeWorkingDir(params[1]);
  } else if ( command.compare("REST") == 0 ){
    cout << this->pi.commandRestart();
  } else if ( command.compare("NOOP") == 0 ){
    cout << this->pi.commandNoop();
  } else if ( command.compare("LIST") == 0 ){
    DTP dtp;
    enterPassiveMode(&dtp);
    cout << this->pi.commandList();
    cout << dtp.receiveList();
  } else if ( command.compare("RETR") == 0 ){
    DTP dtp;
    enterPassiveMode(&dtp);
    cout << this->pi.commandRetrieve(params[1]);
    dtp.receiveFile("shared/" + params[1]);
  } else if ( command.compare("STOR") == 0 ){
    DTP dtp;
    enterPassiveMode(&dtp);
    this->pi.commandStore(params[1]);
    dtp.storeFile("shared/" + params[1]);
    cout << pi.receiveMessage();
    cout << pi.receiveMessage();
  } else if ( command.compare("LS") == 0 ){
    cout << "              Shared directory content:" << endl;
    system("ls shared/ -l");
    cout << endl;
  }
}

// Private

void FTP::setUp(){
  cout << this->pi.commandUser(user);
  cout << this->pi.commandPassword(password);
  cout << this->pi.commandChangeWorkingDir("/shared");
  cout << this->pi.commandSetUTF8Encoding();
  cout << this->pi.commandSetTypeAscii();
  cout << "*************** Ready **************" << endl;
};

void FTP::enterPassiveMode(DTP* dtp){
    string response = this->pi.commandEnterPassiveMode();
    PassiveResponseParser parser(response);
    parser.parse();

    string host = parser.getHost();
    string port = parser.getPort();

    dtp->connect(host, port);
};
