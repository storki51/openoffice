/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/

package complex.storages;

import com.sun.star.uno.XInterface;
import com.sun.star.lang.XMultiServiceFactory;
import com.sun.star.lang.XSingleServiceFactory;
import com.sun.star.lang.DisposedException;

import com.sun.star.bridge.XUnoUrlResolver;
import com.sun.star.uno.UnoRuntime;
import com.sun.star.uno.XInterface;

import com.sun.star.container.XNameAccess;

import com.sun.star.embed.*;

import share.LogWriter;
import complex.storages.TestHelper;
import complex.storages.StorageTest;

public class Test04 implements StorageTest {

	XMultiServiceFactory m_xMSF;
	XSingleServiceFactory m_xStorageFactory;
	TestHelper m_aTestHelper;

	public Test04( XMultiServiceFactory xMSF, XSingleServiceFactory xStorageFactory, LogWriter aLogWriter )
	{
		m_xMSF = xMSF;
		m_xStorageFactory = xStorageFactory;
		m_aTestHelper = new TestHelper( aLogWriter, "Test04: " );
	}

    public boolean test()
	{
		try
		{
			String sTempFileURL = m_aTestHelper.CreateTempFile( m_xMSF );
			if ( sTempFileURL == null || sTempFileURL == "" )
			{
				m_aTestHelper.Error( "No valid temporary file was created!" );
				return false;
			}
		
			// create temporary storage based on arbitrary medium
			// after such a storage is closed it is lost
			Object oTempStorage = m_xStorageFactory.createInstance();
			XStorage xTempStorage = (XStorage) UnoRuntime.queryInterface( XStorage.class, oTempStorage );
			if ( xTempStorage == null )
			{
				m_aTestHelper.Error( "Can't create temporary storage representation!" );
				return false;
			}

			// open substorages and create streams there

			// first substorage of the root storage
			XStorage xTempSubStorage1 = m_aTestHelper.openSubStorage( xTempStorage,
																		"SubStorage1",
																		ElementModes.WRITE );
			if ( xTempSubStorage1 == null )
			{
				m_aTestHelper.Error( "Can't create substorage!" );
				return false;
			}
			
            byte pBigBytes[] = new byte[33000];
			for ( int nInd = 0; nInd < 33000; nInd++ )
				pBigBytes[nInd] = (byte)( nInd % 128 );

			// open a new substream, set "MediaType" and "Compressed" properties to it and write some bytes
			if ( !m_aTestHelper.WriteBytesToSubstream( xTempSubStorage1, "BigSubStream1", "MediaType1", true, pBigBytes ) )
				return false;

			byte pBytes1[] = { 1, 1, 1, 1, 1 };

			// open a new substream, set "MediaType" and "Compressed" properties to it and write some bytes
			if ( !m_aTestHelper.WriteBytesToSubstream( xTempSubStorage1, "SubStream1", "MediaType1", true, pBytes1 ) )
				return false;

			// second substorage of the root storage
			XStorage xTempSubStorage2 = m_aTestHelper.openSubStorage( xTempStorage,
																		"SubStorage2",
																		ElementModes.WRITE );
			if ( xTempSubStorage2 == null )
			{
				m_aTestHelper.Error( "Can't create substorage!" );
				return false;
			}

			// open a new substream, set "MediaType" and "Compressed" properties to it and write some bytes
			if ( !m_aTestHelper.WriteBytesToSubstream( xTempSubStorage2, "BigSubStream2", "MediaType2", false, pBigBytes ) )
				return false;

			byte pBytes2[] = { 2, 2, 2, 2, 2 };

			// open a new substream, set "MediaType" and "Compressed" properties to it and write some bytes
			if ( !m_aTestHelper.WriteBytesToSubstream( xTempSubStorage2, "SubStream2", "MediaType2", false, pBytes2 ) )
				return false;
		
			// set "MediaType" property for storages and check that "IsRoot" and "OpenMode" properties are set correctly
			if ( !m_aTestHelper.setStorageTypeAndCheckProps( xTempStorage,
															"MediaType3",
															true,
															ElementModes.WRITE ) )
				return false;

			// set "MediaType" property for storages and check that "IsRoot" and "OpenMode" properties are set correctly
			if ( !m_aTestHelper.setStorageTypeAndCheckProps( xTempSubStorage1,
															"MediaType4",
															false,
															ElementModes.WRITE ) )
				return false;
	
			// set "MediaType" property for storages and check that "IsRoot" and "OpenMode" properties are set correctly
			if ( !m_aTestHelper.setStorageTypeAndCheckProps( xTempSubStorage2,
															"MediaType5",
															false,
															ElementModes.WRITE ) )
				return false;
	
			// create temporary storage based on a previously created temporary file
			Object pArgs[] = new Object[2];
			pArgs[0] = (Object) sTempFileURL;
			pArgs[1] = new Integer( ElementModes.WRITE );

			Object oTempFileStorage = m_xStorageFactory.createInstanceWithArguments( pArgs );
			XStorage xTempFileStorage = (XStorage)UnoRuntime.queryInterface( XStorage.class, oTempFileStorage );
			if ( xTempFileStorage == null )
			{
				m_aTestHelper.Error( "Can't create storage based on temporary file!" );
				return false;
			}

			if ( !m_aTestHelper.copyElementTo( xTempStorage, "SubStorage1", xTempFileStorage ) )
				return false;

			// if storage is not commited before disposing all the changes will be lost
			if ( !m_aTestHelper.commitStorage( xTempSubStorage2 ) )
				return false;

			// a storage must be disposed before moving/removing otherwise the access will be denied
			if ( !m_aTestHelper.disposeStorage( xTempSubStorage2 ) )
				return false;

			if ( !m_aTestHelper.moveElementTo( xTempStorage, "SubStorage2", xTempFileStorage ) )
				return false;

			// SubStorage2 must be removed and disposed now
			try
			{
				xTempSubStorage2.isStreamElement( "SubStream2" );
				m_aTestHelper.Error( "SubStorage2 must be disposed already!" );
				return false;
			}
			catch( com.sun.star.lang.DisposedException de )
			{
			}
			catch( Exception e )
			{
				m_aTestHelper.Error( "Wrong exception in case of disposed storage, exception: " + e );
				return false;
			}

			if ( !m_aTestHelper.copyElementTo( xTempSubStorage1, "SubStream1", xTempFileStorage ) )
				return false;

			if ( !m_aTestHelper.renameElement( xTempFileStorage, "SubStream1", "SubStream1_copy" ) )
				return false;

			if ( !m_aTestHelper.moveElementTo( xTempSubStorage1, "SubStream1", xTempFileStorage ) )
				return false;

			if ( !m_aTestHelper.copyElementTo( xTempSubStorage1, "BigSubStream1", xTempFileStorage ) )
				return false;

			if ( !m_aTestHelper.renameElement( xTempFileStorage, "BigSubStream1", "BigSubStream1_copy" ) )
				return false;

			if ( !m_aTestHelper.moveElementTo( xTempSubStorage1, "BigSubStream1", xTempFileStorage ) )
				return false;

			if ( !m_aTestHelper.commitStorage( xTempFileStorage ) )
				return false;

			// dispose used storages to free resources
			if ( !m_aTestHelper.disposeStorage( xTempStorage ) || !m_aTestHelper.disposeStorage( xTempFileStorage ) )
				return false;

			// ================================================
			// now check all the written and copied information
			// ================================================

			// the temporary file must not be locked any more after storage disposing
			pArgs[1] = new Integer( ElementModes.WRITE );
			Object oResStorage = m_xStorageFactory.createInstanceWithArguments( pArgs );
			XStorage xResStorage = (XStorage) UnoRuntime.queryInterface( XStorage.class, oResStorage );
			if ( xResStorage == null )
			{
				m_aTestHelper.Error( "Can't reopen storage based on temporary file!" );
				return false;
			}

			// open and check SubStorage1
			XStorage xResSubStorage1 = m_aTestHelper.openSubStorage( xResStorage,
																		"SubStorage1",
																		ElementModes.READ );
			if ( xResSubStorage1 == null )
			{
				m_aTestHelper.Error( "Can't open existing substorage!" );
				return false;
			}
	
			if ( !m_aTestHelper.checkStorageProperties( xResSubStorage1, "MediaType4", false, ElementModes.READ ) )
				return false;


			// open and check SubStorage2
			XStorage xResSubStorage2 = m_aTestHelper.openSubStorage( xResStorage,
																		"SubStorage2",
																		ElementModes.READ );
			if ( xResSubStorage2 == null )
			{
				m_aTestHelper.Error( "Can't open existing substorage!" );
				return false;
			}

			if ( !m_aTestHelper.checkStorageProperties( xResSubStorage2, "MediaType5", false, ElementModes.READ ) )
				return false;


			// check all the result streams

			if ( !m_aTestHelper.checkStream( xResStorage, "SubStream1", "MediaType1", true, pBytes1 ) )
				return false;

			if ( !m_aTestHelper.checkStream( xResStorage, "BigSubStream1", "MediaType1", true, pBigBytes ) )
				return false;

			if ( !m_aTestHelper.checkStream( xResStorage, "SubStream1_copy", "MediaType1", true, pBytes1 ) )
				return false;

			if ( !m_aTestHelper.checkStream( xResStorage, "BigSubStream1_copy", "MediaType1", true, pBigBytes ) )
				return false;

			if ( !m_aTestHelper.checkStream( xResSubStorage1, "SubStream1", "MediaType1", true, pBytes1 ) )
				return false;

			if ( !m_aTestHelper.checkStream( xResSubStorage1, "BigSubStream1", "MediaType1", true, pBigBytes ) )
				return false;

			if ( !m_aTestHelper.checkStream( xResSubStorage2, "SubStream2", "MediaType2", false, pBytes2 ) )
				return false;

			if ( !m_aTestHelper.checkStream( xResSubStorage2, "BigSubStream2", "MediaType2", false, pBigBytes ) )
				return false;

			// the storage must be disposed before removing
			if ( !m_aTestHelper.disposeStorage( xResSubStorage2 ) )
				return false;

			// remove element and check that it was removed completelly
			if ( !m_aTestHelper.removeElement( xResStorage, "SubStorage2" ) )
				return false;
				
			try
			{
				XNameAccess xResAccess = (XNameAccess) UnoRuntime.queryInterface( XNameAccess.class, xResStorage );
				if ( xResAccess.hasByName( "SubStorage2" ) )
					m_aTestHelper.Error( "SubStorage2 must be removed already!" );
			}
			catch( Exception e )
			{
				m_aTestHelper.Error( "Can't get access to root storage, exception: " + e );
				return false;
			}

			try
			{
				xResSubStorage2.isStreamElement( "SubStream2" );

				m_aTestHelper.Error( "SubStorage2 must be disposed already!" );
				return false;
			}
			catch( com.sun.star.lang.DisposedException de )
			{
			}
			catch( Exception e )
			{
				m_aTestHelper.Error( "Wrong exception in case of disposed storage, exception: " + e );
				return false;
			}

			// dispose used storages to free resources
			if ( !m_aTestHelper.disposeStorage( xResStorage ) )
				return false;

			return true;
		}
		catch( Exception e )
		{
			m_aTestHelper.Error( "Exception: " + e );
			return false;
		}
    } 

}

