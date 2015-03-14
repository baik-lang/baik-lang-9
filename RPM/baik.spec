Summary:Baik Programming Language
Name:baik
Version:9.0
Release:1
License:Baik
Group:System Environment/Base
URL:http://sourceforge.net/projects/baik/
Source0:https://github.com/anak10thn/baik-lang/archive/baik-9.0.tar.gz
BuildRoot:%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires:mariadb-server
Requires:sqlite
Requires:openlibm
Requires:gd
BuildRequires:gcc
BuildRequires:mariadb-devel
BuildRequires:sqlite-devel
BuildRequires:openlibm-devel
BuildRequires:gd-devel
%description
BAIK is a scripting language which syntax is 
in Indonesian for Linux and Windows. It supports Animation, 
PDF, UTF8, Printer, OOP, GUI, CGI, Databases, Graphics and TCP/IP.

%prep
%setup -q -n %{name}-lang-%{name}-%{version}

%install
install -d -m 755 $RPM_BUILD_ROOT/usr/bin
make
cp -rf baik $RPM_BUILD_ROOT/usr/bin

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
/usr/bin/baik

%changelog
* Sat Mar 14 2015 ibnu yahya <anak10thn@gmail.com>
- BUILD : version 9.0
