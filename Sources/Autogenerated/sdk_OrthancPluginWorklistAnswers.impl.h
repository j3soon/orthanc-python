/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2022 Osimis S.A., Belgium
 * Copyright (C) 2021-2022 Sebastien Jodogne, ICTEAM UCLouvain, Belgium
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


// Forward declaration of the autogenerated methods
static PyObject *sdk_OrthancPluginWorklistAnswers_OrthancPluginWorklistMarkIncomplete(
  sdk_OrthancPluginWorklistAnswers_Object* self, PyObject *args);
// End of forward declarations


// Forward declaration of the custom methods
extern PyObject *WorklistAddAnswer(
  sdk_OrthancPluginWorklistAnswers_Object* self, PyObject *args);
// End of forward declarations


static PyMethodDef sdk_OrthancPluginWorklistAnswers_Methods[] = {
  { "WorklistMarkIncomplete",
    (PyCFunction) sdk_OrthancPluginWorklistAnswers_OrthancPluginWorklistMarkIncomplete, METH_VARARGS,
    "Generated from C function OrthancPluginWorklistMarkIncomplete()" },
  { "WorklistAddAnswer",
    (PyCFunction) WorklistAddAnswer, METH_VARARGS,
    "Generated from C function OrthancPluginWorklistAddAnswer()" },
  { NULL }  /* Sentinel */
};


static int sdk_OrthancPluginWorklistAnswers_Constructor(
  sdk_OrthancPluginWorklistAnswers_Object *self, PyObject *args, PyObject *kwds)
{
  PythonLock::LogCall("Creating Python object of class OrthancPluginWorklistAnswers");

  self->object_ = NULL;
  self->borrowed_ = false;
  
  long long object = 0;
  unsigned char borrowed = false;
  
  if (PyArg_ParseTuple(args, "Lb", &object, &borrowed))
  {
    self->object_ = reinterpret_cast<OrthancPluginWorklistAnswers*>(static_cast<intptr_t>(object));
    self->borrowed_ = borrowed;
    return 0;
  }
  else
  {
    PyErr_SetString(PyExc_ValueError, "Expected a pair (pointer, borrowed) in the constructor");
    return -1;
  }
}


/**
 * Static global structure => the fields that are beyond the last
 * initialized field are set to zero.
 * https://stackoverflow.com/a/11152199/881731
 **/
static PyTypeObject sdk_OrthancPluginWorklistAnswers_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.WorklistAnswers",    /* tp_name */
  sizeof(sdk_OrthancPluginWorklistAnswers_Object), /* tp_basicsize */
};




// Actual implementation of the methods
static PyObject *sdk_OrthancPluginWorklistAnswers_OrthancPluginWorklistMarkIncomplete(
  sdk_OrthancPluginWorklistAnswers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginWorklistMarkIncomplete() on object of class OrthancPluginWorklistAnswers");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }


  OrthancPluginErrorCode code = OrthancPluginWorklistMarkIncomplete(OrthancPlugins::GetGlobalContext(), self->object_);
  

  if (code == OrthancPluginErrorCode_Success)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }
  else
  {
    PythonLock::RaiseException(code);
    return NULL;
  }
}



static void RegisterOrthancPluginWorklistAnswersClass(PyObject* module)
{
  sdk_OrthancPluginWorklistAnswers_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginWorklistAnswers_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginWorklistAnswers_Type.tp_doc = "Generated from Orthanc C class: OrthancPluginWorklistAnswers";
  sdk_OrthancPluginWorklistAnswers_Type.tp_methods = sdk_OrthancPluginWorklistAnswers_Methods;
  sdk_OrthancPluginWorklistAnswers_Type.tp_init = (initproc) sdk_OrthancPluginWorklistAnswers_Constructor;

  
  if (PyType_Ready(&sdk_OrthancPluginWorklistAnswers_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginWorklistAnswers");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  Py_INCREF(&sdk_OrthancPluginWorklistAnswers_Type);
  if (PyModule_AddObject(module, "WorklistAnswers", (PyObject *)&sdk_OrthancPluginWorklistAnswers_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginWorklistAnswers");
    Py_DECREF(&sdk_OrthancPluginWorklistAnswers_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


PyTypeObject* GetOrthancPluginWorklistAnswersType()
{
  return &sdk_OrthancPluginWorklistAnswers_Type;
}
