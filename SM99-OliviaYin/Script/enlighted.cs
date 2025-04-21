using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering.Universal;

public class enlighted : MonoBehaviour
{
    public Light2D light2d;
    public ParticleSystem flame;
    public ParticleSystem glow;
    public ParticleSystem spark;
    public GameObject platform;

    bool turnedOn;

    private IEnumerator coroutine;


    // Start is called before the first frame update
    void Start()
    {
        //light2d = gameObject.GetComponent<Light2D>();
        //flame = flame.gameObject.GetComponent<ParticleSystem>();
        //glow = gameObject.GetComponent<ParticleSystem>();
        //spark = gameObject.GetComponent<ParticleSystem>();

        light2d.intensity = 0;
        flame.Stop();
        glow.Stop();
        spark.Stop();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        //Debug.Log(collision.name);
        if (turnedOn && collision.tag == "platform")
        {
            collision.GetComponent<changePlatform>().changeWhiteColor();

        }
    }

    public void turnOnLight()
    {
        light2d.intensity = 1;
        flame.Play();
        glow.Play();
        spark.Play();

        StartCoroutine(lightCounter());
    }

    public void lightPlatform()
    {
        platform.gameObject.GetComponent<changePlatform>().changeWhiteColor();
    }

    IEnumerator lightCounter()
    {
        yield return new WaitForSeconds(.5f);
        lightPlatform();
    }
}
