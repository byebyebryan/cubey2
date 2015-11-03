#pragma once

#include <iostream>
#include <string>

namespace cubey2 {
	template<typename ServiceInterfaceT>
	class IService {
	public:
		virtual ~IService() {}

		virtual void Init() {}
		virtual void StartUp() {}
		virtual void Pause() {}
		virtual void Resume() {}
		virtual void ShutDown() {}
		virtual void Destroy() {}

		static ServiceInterfaceT* GetInstance();

		template<typename ServiceT = ServiceInterfaceT>
		static void InitService(ServiceT* _new_service = nullptr);

		static void StartUpService();
		static void PauseService();
		static void ResumeService();
		static void ShutDownService();
		static void DestroyService();
	};

	template<typename ServiceInterfaceT>
	class ServiceLocator {
	public:
		static ServiceInterfaceT* service() {
			return service_;
		}

		static void set_service(ServiceInterfaceT* _service) {
			service_ = _service;
		}

		template<typename ServiceT = ServiceInterfaceT>
		static void InitService(ServiceT* _new_service = nullptr) {
			if (service_) {
				ShutDownService();
				DestroyService();
			}
			if (!_new_service) {
				_new_service = new ServiceT();
			}
			_new_service->Init();
			set_service(_new_service);
		}

		static void StartUpService() {
			if (service_) {
				service_->StartUp();
			}
		}

		static void PauseService() {
			if (service_) {
				service_->Pause();
			}
		}

		static void ResumeService() {
			if (service_) {
				service_->Resume();
			}
		}

		static void ShutDownService() {
			if (service_) {
				service_->ShutDown();
			}
		}

		static void DestroyService() {
			if (service_) {
				service_->Destroy();
				delete service_;
			}
		}
	private:
		static ServiceInterfaceT* service_;
	};

	template<typename ServiceInterfaceT>
	ServiceInterfaceT* ServiceLocator<ServiceInterfaceT>::service_ = nullptr;

	template<typename ServiceInterfaceT>
	inline ServiceInterfaceT * IService<ServiceInterfaceT>::GetInstance() {
		return ServiceLocator<ServiceInterfaceT>::service();
	}

	template<typename ServiceInterfaceT>
	template<typename ServiceT>
	inline void IService<ServiceInterfaceT>::InitService(ServiceT * _new_service) {
		ServiceLocator<ServiceInterfaceT>::InitService<ServiceT>();
	}

	template <typename ServiceInterfaceT>
	void IService<ServiceInterfaceT>::StartUpService() {
		ServiceLocator<ServiceInterfaceT>::StartUpService();
	}

	template <typename ServiceInterfaceT>
	void IService<ServiceInterfaceT>::PauseService() {
		ServiceLocator<ServiceInterfaceT>::PauseService();
	}

	template <typename ServiceInterfaceT>
	void IService<ServiceInterfaceT>::ResumeService() {
		ServiceLocator<ServiceInterfaceT>::ResumeService();
	}

	template <typename ServiceInterfaceT>
	void IService<ServiceInterfaceT>::ShutDownService() {
		ServiceLocator<ServiceInterfaceT>::ShutDownService();
	}

	template <typename ServiceInterfaceT>
	void IService<ServiceInterfaceT>::DestroyService() {
		ServiceLocator<ServiceInterfaceT>::DestroyService();
	}
}