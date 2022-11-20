using UnityEngine;
using System.Collections;

public class ReceivePosition : MonoBehaviour
{

	public OSC osc;
	public dialogue dialogue;


	// Use this for initialization
	void Start()
	{
		osc.SetAddressHandler("/rect", moveCube);
	}

	// Update is called once per frame
	void Update()
	{

	}

    private void OnTriggerEnter(Collider other)
    {

        if (other.gameObject.tag == "cat")
        {
			Debug.Log("touch");
			dialogue.touched = true;
		}
    }




    void moveCube(OscMessage message)
	{
		float x = message.GetFloat(0);
		float y = message.GetFloat(1);

		float wid = message.GetFloat(2);
		float height = message.GetFloat(3);

		float mapx = Map(x, 0, 640, -0.5f, 0.5f);
		float mapy = Map(y, 0, 480, 0.3f, -0.3f);

		float mapwid = Map(wid, 0, 600, 0, 5f);
		float mapheight = Map(height, 0, 400, 0, 3f);

		transform.position = new Vector2(mapx, mapy +0.1f);
		transform.localScale = new Vector3(mapwid, mapwid, mapwid);
	}

	float Map(float x, float x1, float x2, float y1, float y2)
	{
		float m = (y2 - y1) / (x2 - x1);
		float c = y1 - m * x1; // point of interest: c is also equal to y2 - m * x2, though float math might lead to slightly different results.

		return m * x + c;
	}

}