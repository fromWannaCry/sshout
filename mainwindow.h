/* Secure Shout Host Oriented Unified Talk
 * Copyright 2015-2018 Rivoreo
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "sshclient.h"

class QSettings;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *, QSettings *, const QString &, quint16, const QString &);
	~MainWindow();

protected:
	void keyPressEvent(QKeyEvent *);
	void keyReleaseEvent(QKeyEvent *);
	bool eventFilter(QObject *, QEvent *);
	void closeEvent(QCloseEvent *);

private:
	void print_message(const QString &, const QString &, quint8, const QByteArray &);
	void send_hello();
	void save_ui_layout();
	Ui::MainWindow *ui;
	bool use_internal_ssh_library;
	SSHClient *ssh_client;
	QDataStream *data_stream;
	QString host;
	quint16 port;
	QSettings *config;
	bool send_message_on_enter;
	bool control_key_pressed;
	bool ignore_key_event;
	bool need_reconnect;

private slots:
	void connect_ssh();
	//void on_ssh_state_change(SSHClient::SSHState);
	void ssh_state_change(SSHClient::SSHState);
	//void on_ssh_ready_read();
	//void on_ssh_ready_read_stderr();
	void read_ssh();
	void read_ssh_stderr();
	void set_send_message_on_enter(bool);
	void settings();
	void send_message();
	void change_server();
};

#endif // MAINWINDOW_H
