package com.eavoo.printer;

import java.io.IOException;

import javax.obex.HeaderSet;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

import android.content.Context;
import android.os.Handler;
import android.util.Log;

public class JobBasePrinter extends BluetoothBasePrinter
{
	private static final String TAG = "JobBasePrinter";

	public JobBasePrinter(Context context, Handler handler, BppObexTransport transport, BluetoothPrintJob job)
	{
		super(context, handler, transport, job);
	}

	public BluetoothPrinterAttribute GetPrinterAttributes()
	{
		BluetoothPrinterAttribute attribute = new BluetoothPrinterAttribute(this);

		try
		{
			attribute.update();
			return attribute;
		}
		catch (ParserConfigurationException e)
		{
			e.printStackTrace();
		}
		catch (SAXException e)
		{
			e.printStackTrace();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}

		return null;
	}

	public boolean SendDocument() throws IOException
	{
		return PutFile(mPrintJob.getFileName(), mPrintJob.getDocumentFormat(), mPrintJob.buildHeaderSet(), UUID_DPS);
	}

	public boolean SendDocument(BluetoothPrintJob job, byte[] data, HeaderSet headerSet) throws IOException
	{
		return PutByteArray(UUID_DPS, headerSet, data);
	}

	public boolean WaitPrintComplete()
	{
		while (true)
		{
			if (mPrintJob.getAttributes() == false)
			{
				return false;
			}

			if (mPrintJob.getJobState().equals("completed"))
			{
				break;
			}

			try
			{
				sleep(2000);
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}

		return true;
	}

	public boolean PrintFile() throws IOException, ParserConfigurationException, SAXException
	{
		if (mPrintJob.create(this) == false)
		{
			return false;
		}

		Log.v(TAG, "JobId = " + mPrintJob.getJobId());
		Log.v(TAG, String.format("OperationStatus = 0x%04x", mPrintJob.getOperationStatus()));

		mPrintJob.getAttributes();

		if (SendDocument() == false)
		{
			mPrintJob.cancel();
			return false;
		}

		return WaitPrintComplete();
	}

	@Override
	public boolean BluetoothPrinterRun()
	{
		String extension = BluetoothPrintJob.GetFileExtension(getFileName());

		Log.v(TAG, "File extension = \"" + extension + "\"");

		boolean ret = false;

		try
		{
			ret = PrintFile();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		catch (ParserConfigurationException e)
		{
			e.printStackTrace();
		}
		catch (SAXException e)
		{
			e.printStackTrace();
		}

		if (ret)
		{
			SendMessage(BPP_MSG_JOB_BASE_PRINT_COMPLETE, 0, null);
		}
		else
		{
			SendMessage(BPP_MSG_JOB_BASE_PRINT_COMPLETE, -1, null);
		}

		return ret;
	}
}