%define luaver 5.3
%define lualibdir %{_libdir}/lua/%{luaver}
%define luapkgdir %{_datadir}/lua/%{luaver}

Name:           lua-linuxsys
Version:        5.3.0
Release:        1%{?dist}
Summary:        A Linux system library for Lua

Group:          Development/Libraries
License:        Public Domain
URL:            https://github.com/jthiltges/lua-linuxsys
Source0:        lua-linuxsys-5.3.0.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  lua >= %{luaver}, lua-devel >= %{luaver}
Requires:       lua >= %{luaver}

%description
This is a Linux syscall library for Lua which provides access to some Linux-specific calls
to Lua programs.

%prep
%setup -q -n lua-linuxsys-%{version}


%build
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT DOC=%{_defaultdocdir}/%{name} LUALIB=%{lualibdir} LUAPKG=%{luapkgdir}


%check


%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root,-)
%doc README.md
%{lualibdir}/*
%{luapkgdir}/*.lua
