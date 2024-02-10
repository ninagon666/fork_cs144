#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  // cerr << "Function called: get_URL(" << host << ", " << path << ")\n";
  // cerr << "Warning: get_URL() has not been implemented yet.\n";

  // TCPSocket socket_fd;
  auto socket_fd = TCPSocket();
  auto addr = Address( host, "http" );
  socket_fd.connect( addr );

  string httpRequest = "GET " + string( path ) + " HTTP/1.1\r\n";
  httpRequest += "Host: " + string( host ) + "\r\n";
  httpRequest += "Connection: close\r\n";
  httpRequest += "\r\n";
  // cout << httpRequest << "\r\n";
  socket_fd.write( httpRequest );

  string recv_buff;
  // 只读取一次并不能将所有数据读取出来
  //  socket_fd.read(recv_buff);
  //  cout << recv_buff;

  while ( !socket_fd.eof() ) {
    socket_fd.read( recv_buff );
    cout << recv_buff;
  }

  socket_fd.shutdown( SHUT_RDWR );
  socket_fd.close();
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
