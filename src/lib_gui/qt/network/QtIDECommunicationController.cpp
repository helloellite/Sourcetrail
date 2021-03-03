#include "QtIDECommunicationController.h"

#include <functional>

#include "ProjectSettings.h"
#include "Application.h"
#include "MessageStatus.h"

QtIDECommunicationController::QtIDECommunicationController(QObject* parent, StorageAccess* storageAccess)
	: IDECommunicationController(storageAccess), m_tcpWrapper(parent)
{
	m_tcpWrapper.setReadCallback(std::bind(
		&QtIDECommunicationController::handleIncomingMessage, this, std::placeholders::_1));
}

QtIDECommunicationController::~QtIDECommunicationController() {}

void QtIDECommunicationController::startListening()
{
	if (!Application::getInstance()->getCurrentProject())
		//LOG_INFO("IDE connect should open an project.");
		return;
	m_onQtThread([=]() {
		auto appSettings = Application::getInstance()->getCurrentProject()->getProjectSetting();
		auto sp = appSettings->getSourcetrailPort();
		auto pp = appSettings->getPluginPort();
		m_tcpWrapper.setServerPort(sp);
		m_tcpWrapper.setClientPort(pp);
		m_tcpWrapper.startListening();
		MessageStatus(
			L"Start Listening IDE<" + std::to_wstring(pp) + L"> at port <" + std::to_wstring(sp) + L">"
		).dispatch();
		sendUpdatePing();
	});
}

void QtIDECommunicationController::stopListening()
{
	m_onQtThread([=]() { m_tcpWrapper.stopListening(); });
}

bool QtIDECommunicationController::isListening() const
{
	return m_tcpWrapper.isListening();
}

void QtIDECommunicationController::handleMessage(MessagePluginPortChange * message)
{
	if (message->pluginPort && message->pluginPort == m_tcpWrapper.getClientPort() && message->sourcetrailPort == m_tcpWrapper.getServerPort())
		// pluginPort==0 means no port information.
		return;
	stopListening();
	startListening();
}

void QtIDECommunicationController::sendMessage(const std::wstring& message) const
{
	m_tcpWrapper.sendMessage(message);
}
