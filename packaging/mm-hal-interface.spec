Name:       mm-hal-interface
Summary:    Multimedia HAL Interface
Version:    0.0.2
Release:    0
Group:      Multimedia/Development
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildArch:  noarch

%description
Multimedia framework hardware abstraction layer interface package.

%prep
%setup -q

%install
install -d -m 755 %{buildroot}%{_includedir}
install -m 644 audio/*.h %{buildroot}%{_includedir}
install -m 644 camera/*.h %{buildroot}%{_includedir}
install -m 644 radio/*.h %{buildroot}%{_includedir}
mkdir -p %{buildroot}%{_datadir}/license
cp LICENSE.APLv2 %{buildroot}%{_datadir}/license/%{name}

%files
%defattr(-,root,root,-)
%{_includedir}/*.h
%{_datadir}/license/%{name}

