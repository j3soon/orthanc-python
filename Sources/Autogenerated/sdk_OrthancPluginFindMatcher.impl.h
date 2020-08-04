/**
 * Python plugin for Orthanc
 * Copyright (C) 2017-2020 Osimis S.A., Belgium
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


typedef struct 
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginFindMatcher* object_;
  bool borrowed_;
} sdk_OrthancPluginFindMatcher_Object;



// Forward declaration of the methods
static PyObject *sdk_OrthancPluginFindMatcher_OrthancPluginFindMatcherIsMatch(
  sdk_OrthancPluginFindMatcher_Object* self, PyObject *args);


static PyMethodDef sdk_OrthancPluginFindMatcher_Methods[] = {
  { "FindMatcherIsMatch",
    (PyCFunction) sdk_OrthancPluginFindMatcher_OrthancPluginFindMatcherIsMatch, METH_VARARGS,
    "Generated from C function OrthancPluginFindMatcherIsMatch()" },
  { NULL }  /* Sentinel */
};


static int sdk_OrthancPluginFindMatcher_Constructor(
  sdk_OrthancPluginFindMatcher_Object *self, PyObject *args, PyObject *kwds)
{
  PythonLock::LogCall("Creating Python object of class OrthancPluginFindMatcher");

  self->object_ = NULL;
  self->borrowed_ = false;
  
  long long object = 0;
  unsigned char borrowed = false;
  
  if (PyArg_ParseTuple(args, "Lb", &object, &borrowed))
  {
    self->object_ = reinterpret_cast<OrthancPluginFindMatcher*>(static_cast<intptr_t>(object));
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
static PyTypeObject sdk_OrthancPluginFindMatcher_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.FindMatcher",    /* tp_name */
  sizeof(sdk_OrthancPluginFindMatcher_Object), /* tp_basicsize */
};


static void sdk_OrthancPluginFindMatcher_Destructor(PyObject *self)
{
  PythonLock::LogCall("Destroying Python object of class OrthancPluginFindMatcher");

  sdk_OrthancPluginFindMatcher_Object& tmp = *((sdk_OrthancPluginFindMatcher_Object*) self);
  
  if (tmp.object_ != NULL &&
      !tmp.borrowed_)
  {
    OrthancPluginFreeFindMatcher(OrthancPlugins::GetGlobalContext(), tmp.object_);
    tmp.object_ = NULL;
  }
  
  Py_TYPE(self)->tp_free((PyObject *)self);
}


// Actual implementation of the methods
static PyObject *sdk_OrthancPluginFindMatcher_OrthancPluginFindMatcherIsMatch(
  sdk_OrthancPluginFindMatcher_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginFindMatcherIsMatch() on object of class OrthancPluginFindMatcher");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  Py_buffer arg0;

  if (!PyArg_ParseTuple(args, "s*", &arg0))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }
  long value = OrthancPluginFindMatcherIsMatch(OrthancPlugins::GetGlobalContext(), self->object_, arg0.buf, arg0.len);
  PyBuffer_Release(&arg0);
  return PyLong_FromLong(value);
}



static void RegisterOrthancPluginFindMatcherClass(PyObject* module)
{
  sdk_OrthancPluginFindMatcher_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginFindMatcher_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginFindMatcher_Type.tp_doc = "Generated from Orthanc C class: OrthancPluginFindMatcher";
  sdk_OrthancPluginFindMatcher_Type.tp_methods = sdk_OrthancPluginFindMatcher_Methods;
  sdk_OrthancPluginFindMatcher_Type.tp_init = (initproc) sdk_OrthancPluginFindMatcher_Constructor;

  /**
   * "tp_dealloc is called when the reference count of the object goes
   * down to zero. This is where you destroy the object and its
   * members. It should then free the memory occupied by the object by
   * calling tp_free."
   * https://stackoverflow.com/a/24863227/881731
   **/
  sdk_OrthancPluginFindMatcher_Type.tp_dealloc = sdk_OrthancPluginFindMatcher_Destructor;
  
  if (PyType_Ready(&sdk_OrthancPluginFindMatcher_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginFindMatcher");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  Py_INCREF(&sdk_OrthancPluginFindMatcher_Type);
  if (PyModule_AddObject(module, "FindMatcher", (PyObject *)&sdk_OrthancPluginFindMatcher_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginFindMatcher");
    Py_DECREF(&sdk_OrthancPluginFindMatcher_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


PyObject* GetOrthancPluginFindMatcherType()
{
  return (PyObject*) &sdk_OrthancPluginFindMatcher_Type;
}