/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2021 Osimis S.A., Belgium
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 **/


#include "IncomingInstanceFilter.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"
#include "Autogenerated/sdk.h"
#include "ICallbackRegistration.h"
#include "PythonString.h"


static PyObject*   incomingCStoreInstanceFilter_ = NULL;


static int32_t IncomingCStoreInstanceFilter(const OrthancPluginDicomInstance *instance)
{
  try
  {
    PythonLock lock;

    /**
     * Construct an instance object of the "orthanc.DicomInstance"
     * class. This is done by calling the constructor function
     * "sdk_OrthancPluginDicomInstance_Type".
     **/
    PythonObject args(lock, PyTuple_New(2));
    PyTuple_SetItem(args.GetPyObject(), 0, PyLong_FromSsize_t((intptr_t) instance));
    PyTuple_SetItem(args.GetPyObject(), 1, PyBool_FromLong(true /* borrowed, don't destruct */));
    PyObject *pInst = PyObject_CallObject((PyObject*) GetOrthancPluginDicomInstanceType(), args.GetPyObject());
    
    /**
     * Construct the arguments tuple (instance)
     **/
    PythonObject args2(lock, PyTuple_New(1));
    PyTuple_SetItem(args2.GetPyObject(), 0, pInst);

    PythonObject result(lock, PyObject_CallObject(incomingCStoreInstanceFilter_, args2.GetPyObject()));

    std::string traceback;
    if (lock.HasErrorOccurred(traceback))
    {
      OrthancPlugins::LogError("Error in the Python incoming-cstore-instance callback, "
                               "traceback:\n" + traceback);
      return -1;
    }
    else
    {
      if (PyLong_Check(result.GetPyObject()))
      {
        return static_cast<int32_t>(PyLong_AsLong(result.GetPyObject()));
      }
      else
      {
        OrthancPlugins::LogError("The Python incoming-cstore-instance filter has not returned an integer");
        return -1;
      }
    }
  }
  catch (OrthancPlugins::PluginException& e)
  {
    return e.GetErrorCode();
  }
}

   
PyObject* RegisterIncomingCStoreInstanceFilter(PyObject* module, PyObject* args)
{
  // The GIL is locked at this point (no need to create "PythonLock")

  class Registration : public ICallbackRegistration
  {
  public:
    virtual void Register() ORTHANC_OVERRIDE
    {
      OrthancPluginRegisterIncomingCStoreInstanceFilter(
        OrthancPlugins::GetGlobalContext(), IncomingCStoreInstanceFilter);
    }
  };

  Registration registration;
  return ICallbackRegistration::Apply(
    registration, args, incomingCStoreInstanceFilter_, "Python incoming CStore instance filter");
}


void FinalizeIncomingCStoreInstanceFilter()
{
  ICallbackRegistration::Unregister(incomingCStoreInstanceFilter_);
}
